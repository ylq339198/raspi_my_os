(1)learn_kernel 文件夹是 v1 branch
(2)
learn_kernel_v1_debug_bk.zip enable_mmu_debug_bk_20240425.zip 是为了最开始调试enable_mmu不能在qemu-8.0上运行时，
与lern_kernel比较调试的过程。
最后原因是:enable_mmu中MMU中没有配置EL0，EL1上的虚拟地址位数(即:
#define TCR_T0SZ			(64 - 48) 
#define TCR_T1SZ			((64 - 48) << 16)
)
#define TCR_VALUE                                                        \
    (TCR_IPS |    TCR_T0SZ |  TCR_T1SZ |                                  \
     TCR_TG1_4K | TCR_SH1_INNER | TCR_ORGN1_IRGN1_WRITEBACK_WRITEALLOC | \
     TCR_TG0_4K | TCR_SH0_INNER | TCR_ORGN0_IRGN0_WRITEBACK_WRITEALLOC)
