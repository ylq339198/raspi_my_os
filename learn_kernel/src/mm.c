#include "mmu.h"
#include "current.h"
#include "mm.h"
#include "sysregs.h"

#define PAGE_NUM         (DEVICE_BASE - LOW_MEMORY)/PAGESIZE
static char mem_map[PAGE_NUM] = {0,};

unsigned long get_free_page()
{
    for(int i = 0 ; i< PAGE_NUM ; i++)
    {
        if(!mem_map[i])
	    {
            mem_map[i] = 1;
			unsigned long page = LOW_MEMORY + i * PAGESIZE;
			memzero(page + VA_START, PAGESIZE);
			return page;
	    }
    }
    return 0;
}


void free_page(unsigned long p)
{
    mem_map[(p - LOW_MEMORY)/PAGESIZE] = 0;
}

void * allocate_kernel_page() {
	unsigned long page = get_free_page();
	if (page == 0) {
		return 0;
	}
	return (void *)(page + VA_START);
}



void map_table_entry(unsigned long *pte, unsigned long va, unsigned long pa) {
	unsigned long index = va >> PAGE_SHIFT;
	index = index & (PTRS_PER_TABLE - 1);
	unsigned long entry = pa | MMU_PTE_FLAGS; 
	pte[index] = entry;
}

unsigned long map_table(unsigned long *table, unsigned long shift, unsigned long va, int* new_table) {
	unsigned long index = va >> shift;
	index = index & (PTRS_PER_TABLE - 1);
	if (!table[index]){
		*new_table = 1;
		unsigned long next_level_table = get_free_page();
		unsigned long entry = next_level_table | MM_TYPE_PAGE_TABLE;
		table[index] = entry;
		return next_level_table;
	} else {
		*new_table = 0;
	}
	return table[index] & PAGE_MASK;
}

void map_page(struct task_struct *task, unsigned long va, unsigned long page){
	unsigned long pgd;
	if (!task->mm.pgd) {
		task->mm.pgd = get_free_page();
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = task->mm.pgd;
	}
	pgd = task->mm.pgd;
	int new_table;
	unsigned long pud = map_table((unsigned long *)(pgd + VA_START), PGD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pud;
	}
	unsigned long pmd = map_table((unsigned long *)(pud + VA_START) , PUD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pmd;
	}
	unsigned long pte = map_table((unsigned long *)(pmd + VA_START), PMD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pte;
	}
	map_table_entry((unsigned long *)(pte + VA_START), va, page);
	struct user_page p = {page, va};
	task->mm.user_pages[task->mm.user_pages_count++] = p;
}

void * allocate_user_page(struct task_struct *task, unsigned long va) {
	unsigned long page = get_free_page();
	if (page == 0) {
		return 0;
	}
	map_page(task, va, page);
	return (void *)(page + VA_START);
}

int copy_virt_memory(struct task_struct *dst)
{
	struct task_struct* src = current;
	for (int i = 0; i < src->mm.user_pages_count; i++) {
		unsigned long kernel_va = (unsigned long)allocate_user_page(dst, src->mm.user_pages[i].virt_addr);
		if( kernel_va == 0) {
			return -1;
		}
		memcpy(kernel_va, src->mm.user_pages[i].virt_addr, PAGE_SIZE);
	}
	return 0;
}

static int ind = 1;
int do_mem_abort(unsigned long addr, unsigned long esr) {
	unsigned long dfs = (esr & 0b111111);
	if ((dfs & 0b111100) == 0b100) {
		unsigned long page = get_free_page();
		if (page == 0) {
			return -1;
		}
		map_page(current, addr & PAGE_MASK, page);
		ind++;
		if (ind > 2){
			return -1;
		}
		return 0;
	}
	return -1;
}

int kernel_map(unsigned long va)
{
	int new_table = 0;
	unsigned long pgd = read_sysreg(ttbr1_el1);
	unsigned long pud = map_table((unsigned long *)(pgd + VA_START), PGD_SHIFT, va, &new_table);
	if (new_table) {
		current->mm.kernel_pages[++current->mm.kernel_pages_count] = pud;
	}
	unsigned long pmd = map_table((unsigned long *)(pud + VA_START) , PUD_SHIFT, va, &new_table);
	if (new_table) {
		current->mm.kernel_pages[++current->mm.kernel_pages_count] = pmd;
	}
	unsigned long pte = map_table((unsigned long *)(pmd + VA_START), PMD_SHIFT, va, &new_table);
	if (new_table) {
		current->mm.kernel_pages[++current->mm.kernel_pages_count] = pte;
	}
	map_table_entry((unsigned long *)(pte + VA_START), va, (va - VA_START));
}
