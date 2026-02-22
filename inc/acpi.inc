(*
 * -----------------------------------------------------
 * Common structures provided by the ACPI specification
 * -----------------------------------------------------
 *)

{ NOTE: FreePascal does not support flexible array members.
  Using a dynamic array would add a pointer to the end of the record.
  Instead, an empty record will be used to get the start of the array without any pointer arithmetic. }

const
  ACPI_RSDP_SIGNATURE = 'RSD PTR ';
  ACPI_RSDT_SIGNATURE = 'RSDT';
  ACPI_XSDT_SIGNATURE = 'XSDT';
  ACPI_MADT_SIGNATURE = 'APIC';
  ACPI_FADT_SIGNATURE = 'FACP';
  ACPI_FACS_SIGNATURE = 'FACS';
  ACPI_MCFG_SIGNATURE = 'MCFG';
  ACPI_HPET_SIGNATURE = 'HPET';
  ACPI_SRAT_SIGNATURE = 'SRAT';
  ACPI_SLIT_SIGNATURE = 'SLIT';
  ACPI_DSDT_SIGNATURE = 'DSDT';
  ACPI_SSDT_SIGNATURE = 'SSDT';
  ACPI_PSDT_SIGNATURE = 'PSDT';
  ACPI_ECDT_SIGNATURE = 'ECDT';
  ACPI_RHCT_SIGNATURE = 'RHCT';

  ACPI_AS_ID_SYS_MEM = $00;
  ACPI_AS_ID_SYS_IO = $01;
  ACPI_AS_ID_PCI_CFG_SPACE = $02;
  ACPI_AS_ID_EC = $03;
  ACPI_AS_ID_SMBUS = $04;
  ACPI_AS_ID_SYS_CMOS = $05;
  ACPI_AS_ID_PCI_BAR_TGT = $06;
  ACPI_AS_ID_IPMI = $07;
  ACPI_AS_ID_GP_IO = $08;
  ACPI_AS_ID_GENERIC_SBUS = $09;
  ACPI_AS_ID_PCC = $0A;
  ACPI_AS_ID_FFH = $7F;
  ACPI_AS_ID_OEM_BASE = $C0;
  ACPI_AS_ID_OEM_END = $FF;

  ACPI_ACCESS_UD = 0;
  ACPI_ACCESS_BYTE = 1;
  ACPI_ACCESS_WORD = 2;
  ACPI_ACCESS_DWORD = 3;
  ACPI_ACCESS_QWORD = 4;

type
  pacpi_gas = ^tacpi_gas;
  tacpi_gas = packed record
    address_space_id: uacpi_u8;
    register_bit_width: uacpi_u8;
    register_bit_offset: uacpi_u8;
    access_size: uacpi_u8;
    address: uacpi_u64;
  end;
  {$if sizeof(tacpi_gas) <> 12}
    {$error sizeof(tacpi_gas) <> 12}
  {$endif}

  pacpi_rsdp = ^tacpi_rsdp;
  tacpi_rsdp = packed record
    signature: array [0..7] of uacpi_char;
    checksum: uacpi_u8;
    oemid: array [0..5] of uacpi_char;
    revision: uacpi_u8;
    rsdt_addr: uacpi_u32;

    { vvvv available if .revision >= 2.0 only }
    length: uacpi_u32;
    xsdt_addr: uacpi_u64;
    extended_checksum: uacpi_u8;
    rsvd: array [0..2] of uacpi_u8;
  end;
  {$if sizeof(tacpi_rsdp) <> 36}
    {$error sizeof(tacpi_rsdp) <> 36}
  {$endif}

  pacpi_sdt_hdr = ^tacpi_sdt_hdr;
  tacpi_sdt_hdr = packed record
    signature: array [0..3] of uacpi_char;
    length: uacpi_u32;
    revision: uacpi_u8;
    checksum: uacpi_u8;
    oemid: array [0..5] of uacpi_char;
    oem_table_id: array [0..7] of uacpi_char;
    oem_revision: uacpi_u32;
    creator_id: uacpi_u32;
    creator_revision: uacpi_u32;
  end;
  {$if sizeof(tacpi_sdt_hdr) <> 36}
    {$error sizeof(tacpi_sdt_hdr) <> 36}
  {$endif}

  pacpi_rsdt = ^tacpi_rsdt;
  tacpi_rsdt = packed record
    hdr: tacpi_sdt_hdr;
    entries: array of uacpi_u32;
  end;

  pacpi_xsdt = ^tacpi_xsdt;
  tacpi_xsdt = packed record
    hdr: tacpi_sdt_hdr;
    entries: array of uacpi_u64;
  end;

  pacpi_entry_hdr = ^tacpi_entry_hdr;
  tacpi_entry_hdr = packed record
    (*
     * - tacpi_madt_entry_type for the APIC table
     * - tacpi_srat_entry_type for the SRAT table
     *)
    &type: uacpi_u8;
    length: uacpi_u8;
  end;

const
  // tacpi_madt->flags
  ACPI_PCAT_COMPAT = 1 shl 0;

type
  tacpi_madt_entry_type = (
    ACPI_MADT_ENTRY_TYPE_LAPIC = 0,
    ACPI_MADT_ENTRY_TYPE_IOAPIC = 1,
    ACPI_MADT_ENTRY_TYPE_INTERRUPT_SOURCE_OVERRIDE = 2,
    ACPI_MADT_ENTRY_TYPE_NMI_SOURCE = 3,
    ACPI_MADT_ENTRY_TYPE_LAPIC_NMI = 4,
    ACPI_MADT_ENTRY_TYPE_LAPIC_ADDRESS_OVERRIDE = 5,
    ACPI_MADT_ENTRY_TYPE_IOSAPIC = 6,
    ACPI_MADT_ENTRY_TYPE_LSAPIC = 7,
    ACPI_MADT_ENTRY_TYPE_PLATFORM_INTERRUPT_SOURCES = 8,
    ACPI_MADT_ENTRY_TYPE_LOCAL_X2APIC = 9,
    ACPI_MADT_ENTRY_TYPE_LOCAL_X2APIC_NMI = $A,
    ACPI_MADT_ENTRY_TYPE_GICC = $B,
    ACPI_MADT_ENTRY_TYPE_GICD = $C,
    ACPI_MADT_ENTRY_TYPE_GIC_MSI_FRAME = $D,
    ACPI_MADT_ENTRY_TYPE_GICR = $E,
    ACPI_MADT_ENTRY_TYPE_GIC_ITS = $F,
    ACPI_MADT_ENTRY_TYPE_MULTIPROCESSOR_WAKEUP = $10,
    ACPI_MADT_ENTRY_TYPE_CORE_PIC = $11,
    ACPI_MADT_ENTRY_TYPE_LIO_PIC = $12,
    ACPI_MADT_ENTRY_TYPE_HT_PIC = $13,
    ACPI_MADT_ENTRY_TYPE_EIO_PIC = $14,
    ACPI_MADT_ENTRY_TYPE_MSI_PIC = $15,
    ACPI_MADT_ENTRY_TYPE_BIO_PIC = $16,
    ACPI_MADT_ENTRY_TYPE_LPC_PIC = $17,
    ACPI_MADT_ENTRY_TYPE_RINTC = $18,
    ACPI_MADT_ENTRY_TYPE_IMSIC = $19,
    ACPI_MADT_ENTRY_TYPE_APLIC = $1A,
    ACPI_MADT_ENTRY_TYPE_PLIC = $1B,
    ACPI_MADT_ENTRY_TYPE_RESERVED = $1C, // 0x1C..0x7F
    ACPI_MADT_ENTRY_TYPE_OEM = $80 // 0x80..0xFF
  );

  pacpi_madt = ^tacpi_madt;
  tacpi_madt = packed record
    hdr: tacpi_sdt_hdr;
    local_interrupt_controller_address: uacpi_u32;
    flags: uacpi_u32;
    // start of tacpi_entry_hdr array
    entries: record end;
  end;
  {$if sizeof(tacpi_madt) <> 44}
    {$error sizeof(tacpi_madt) <> 44}
  {$endif}

const
  (*
   * - tacpi_madt_lapic->flags
   * - tacpi_madt_lsapic->flags
   * - tacpi_madt_x2apic->flags
   *)
  ACPI_PIC_ENABLED = 1 shl 0;
  ACPI_PIC_ONLINE_CAPABLE = 1 shl 1;

type
  pacpi_madt_lapic = ^tacpi_madt_lapic;
  tacpi_madt_lapic = packed record
    hdr: tacpi_entry_hdr;
    uid: uacpi_u8;
    id: uacpi_u8;
    flags: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_lapic) <> 8}
    {$error sizeof(tacpi_madt_lapic) <> 8}
  {$endif}

  pacpi_madt_ioapic = ^tacpi_madt_ioapic;
  tacpi_madt_ioapic = packed record
    hdr: tacpi_entry_hdr;
    id: uacpi_u8;
    rsvd: uacpi_u8;
    address: uacpi_u32;
    gsi_base: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_ioapic) <> 12}
    {$error sizeof(tacpi_madt_ioapic) <> 12}
  {$endif}

const
  (*
   * - tacpi_madt_interrupt_source_override->flags
   * - tacpi_madt_nmi_source->flags
   * - tacpi_madt_lapic_nmi->flags
   * - tacpi_madt_platform_interrupt_source->flags
   * - tacpi_madt_x2apic_nmi->flags
   *)
  ACPI_MADT_POLARITY_MASK = %11;
  ACPI_MADT_POLARITY_CONFORMING = %00;
  ACPI_MADT_POLARITY_ACTIVE_HIGH = %01;
  ACPI_MADT_POLARITY_ACTIVE_LOW = %11;

  ACPI_MADT_TRIGGERING_MASK = %1100;
  ACPI_MADT_TRIGGERING_CONFORMING = %0000;
  ACPI_MADT_TRIGGERING_EDGE = %0100;
  ACPI_MADT_TRIGGERING_LEVEL = %1100;

type
  pacpi_madt_interrupt_source_override = ^tacpi_madt_interrupt_source_override;
  tacpi_madt_interrupt_source_override = packed record
    hdr: tacpi_entry_hdr;
    bus: uacpi_u8;
    source: uacpi_u8;
    gsi: uacpi_u32;
    flags: uacpi_u16;
  end;
  {$if sizeof(tacpi_madt_interrupt_source_override) <> 10}
    {$error sizeof(tacpi_madt_interrupt_source_override) <> 10}
  {$endif}

  pacpi_madt_nmi_source = ^tacpi_madt_nmi_source;
  tacpi_madt_nmi_source = packed record
    hdr: tacpi_entry_hdr;
    flags: uacpi_u16;
    gsi: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_nmi_source) <> 8}
    {$error sizeof(tacpi_madt_nmi_source) <> 8}
  {$endif}

  pacpi_madt_lapic_nmi = ^tacpi_madt_lapic_nmi;
  tacpi_madt_lapic_nmi = packed record
    hdr: tacpi_entry_hdr;
    uid: uacpi_u8;
    flags: uacpi_u16;
    lint: uacpi_u8;
  end;
  {$if sizeof(tacpi_madt_lapic_nmi) <> 6}
    {$error sizeof(tacpi_madt_lapic_nmi) <> 6}
  {$endif}

  tacpi_madt_lapic_address_override = packed record
    hdr: tacpi_entry_hdr;
    rsvd: uacpi_u16;
    address: uacpi_u64;
  end;
  {$if sizeof(tacpi_madt_lapic_address_override) <> 12}
    {$error sizeof(tacpi_madt_lapic_address_override) <> 12}
  {$endif}

  pacpi_madt_iosapic = ^tacpi_madt_iosapic;
  tacpi_madt_iosapic = packed record
    hdr: tacpi_entry_hdr;
    id: uacpi_u8;
    rsvd: uacpi_u8;
    gsi_base: uacpi_u32;
    address: uacpi_u64;
  end;
  {$if sizeof(tacpi_madt_iosapic) <> 16}
    {$error sizeof(tacpi_madt_iosapic) <> 16}
  {$endif}

  pacpi_madt_lsapic = ^tacpi_madt_lsapic;
  tacpi_madt_lsapic = packed record
    hdr: tacpi_entry_hdr;
    acpi_id: uacpi_u8;
    id: uacpi_u8;
    eid: uacpi_u8;
    reserved: array [0..2] of uacpi_u8;
    flags: uacpi_u32;
    uid: uacpi_u32;
    // start of uacpi_char array
    uid_string: record end;
  end;
  {$if sizeof(tacpi_madt_lsapic) <> 16}
    {$error sizeof(tacpi_madt_lsapic) <> 16}
  {$endif}

const
  // tacpi_madt_platform_interrupt_source->platform_flags
  ACPI_CPEI_PROCESSOR_OVERRIDE = 1 shl 0;

type
  pacpi_madt_platform_interrupt_source = ^tacpi_madt_platform_interrupt_source;
  tacpi_madt_platform_interrupt_source = packed record
    hdr: tacpi_entry_hdr;
    flags: uacpi_u16;
    &type: uacpi_u8;
    processor_id: uacpi_u8;
    processor_eid: uacpi_u8;
    iosapic_vector: uacpi_u8;
    gsi: uacpi_u32;
    platform_flags: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_platform_interrupt_source) <> 16}
    {$error sizeof(tacpi_madt_platform_interrupt_source) <> 16}
  {$endif}

  pacpi_madt_x2apic = ^tacpi_madt_x2apic;
  tacpi_madt_x2apic = packed record
    hdr: tacpi_entry_hdr;
    rsvd: uacpi_u16;
    id: uacpi_u32;
    flags: uacpi_u32;
    uid: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_x2apic) <> 16}
    {$error sizeof(tacpi_madt_x2apic) <> 16}
  {$endif}

  pacpi_madt_x2apic_nmi = ^tacpi_madt_x2apic_nmi;
  tacpi_madt_x2apic_nmi = packed record
    hdr: tacpi_entry_hdr;
    flags: uacpi_u16;
    uid: uacpi_u32;
    lint: uacpi_u8;
    reserved: array [0..2] of uacpi_u8;
  end;
  {$if sizeof(tacpi_madt_x2apic_nmi) <> 12}
    {$error sizeof(tacpi_madt_x2apic_nmi) <> 12}
  {$endif}

const
  // tacpi_madt_gicc->flags
  ACPI_GICC_ENABLED = 1 shl 0;
  ACPI_GICC_PERF_INTERRUPT_MODE = 1 shl 1;
  ACPI_GICC_VGIC_MAINTENANCE_INTERRUPT_MODE = 1 shl 2;
  ACPI_GICC_ONLINE_CAPABLE = 1 shl 3;

  // ACPI_GICC_*_INTERRUPT_MODE
  ACPI_GICC_TRIGGERING_EDGE = 1;
  ACPI_GICC_TRIGGERING_LEVEL = 0;

type
  pacpi_madt_gicc = ^tacpi_madt_gicc;
  tacpi_madt_gicc = packed record
    hdr: tacpi_entry_hdr;
    rsvd0: uacpi_u16;
    interface_number: uacpi_u32;
    acpi_id: uacpi_u32;
    flags: uacpi_u32;
    parking_protocol_version: uacpi_u32;
    perf_interrupt_gsiv: uacpi_u32;
    parked_address: uacpi_u64;
    address: uacpi_u64;
    gicv: uacpi_u64;
    gich: uacpi_u64;
    vgic_maitenante_interrupt: uacpi_u32;
    gicr_base_address: uacpi_u64;
    mpidr: uacpi_u64;
    power_efficiency_class: uacpi_u8;
    rsvd1: uacpi_u8;
    spe_overflow_interrupt: uacpi_u16;
    trbe_interrupt: uacpi_u16;
  end;
  {$if sizeof(tacpi_madt_gicc) <> 82}
    {$error sizeof(tacpi_madt_gicc) <> 82}
  {$endif}

  pacpi_madt_gicd = ^tacpi_madt_gicd;
  tacpi_madt_gicd = packed record
    hdr: tacpi_entry_hdr;
    rsvd0: uacpi_u16;
    id: uacpi_u32;
    address: uacpi_u64;
    system_vector_base: uacpi_u32;
    gic_version: uacpi_u8;
    reserved1: array [0..2] of uacpi_u8;
  end;
  {$if sizeof(tacpi_madt_gicd) <> 24}
    {$error sizeof(tacpi_madt_gicd) <> 24}
  {$endif}

const
  // tacpi_madt_gic_msi_frame->flags
  ACPI_SPI_SELECT = 1 shl 0;

type
  pacpi_madt_gic_msi_frame = ^tacpi_madt_gic_msi_frame;
  tacpi_madt_gic_msi_frame = packed record
    hdr: tacpi_entry_hdr;
    rsvd: uacpi_u16;
    id: uacpi_u32;
    address: uacpi_u64;
    flags: uacpi_u32;
    spi_count: uacpi_u16;
    spi_base: uacpi_u16;
  end;
  {$if sizeof(tacpi_madt_gic_msi_frame) <> 24}
    {$error sizeof(tacpi_madt_gic_msi_frame) <> 24}
  {$endif}

  pacpi_madt_gicr = ^tacpi_madt_gicr;
  tacpi_madt_gicr = packed record
    hdr: tacpi_entry_hdr;
    rsvd: uacpi_u16;
    address: uacpi_u64;
    length: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_gicr) <> 16}
    {$error sizeof(tacpi_madt_gicr) <> 16}
  {$endif}

  pacpi_madt_gic_its = ^tacpi_madt_gic_its;
  tacpi_madt_gic_its = packed record
    hdr: tacpi_entry_hdr;
    rsvd0: uacpi_u16;
    id: uacpi_u32;
    address: uacpi_u64;
    rsvd1: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_gic_its) <> 20}
    {$error sizeof(tacpi_madt_gic_its) <> 20}
  {$endif}

  pacpi_madt_multiprocessor_wakeup = ^tacpi_madt_multiprocessor_wakeup;
  tacpi_madt_multiprocessor_wakeup = packed record
    hdr: tacpi_entry_hdr;
    mailbox_version: uacpi_u16;
    rsvd: uacpi_u32;
    mailbox_address: uacpi_u64;
  end;
  {$if sizeof(tacpi_madt_multiprocessor_wakeup) <> 16}
    {$error sizeof(tacpi_madt_multiprocessor_wakeup) <> 16}
  {$endif}

const
  ACPI_CORE_PIC_ENABLED = 1 shl 0;

type
  pacpi_madt_core_pic = ^tacpi_madt_core_pic;
  tacpi_madt_core_pic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    acpi_id: uacpi_u32;
    id: uacpi_u32;
    flags: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_core_pic) <> 15}
    {$error sizeof(tacpi_madt_core_pic) <> 15}
  {$endif}

  pacpi_madt_lio_pic = ^tacpi_madt_lio_pic;
  tacpi_madt_lio_pic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    address: uacpi_u64;
    size: uacpi_u16;
    cascade_vector: uacpi_u16;
    cascade_vector_mapping: uacpi_u64;
  end;
  {$if sizeof(tacpi_madt_lio_pic) <> 23}
    {$error sizeof(tacpi_madt_lio_pic) <> 23}
  {$endif}

  pacpi_madt_ht_pic = ^tacpi_madt_ht_pic;
  tacpi_madt_ht_pic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    address: uacpi_u64;
    size: uacpi_u16;
    cascade_vector: uacpi_u64;
  end;
  {$if sizeof(tacpi_madt_ht_pic) <> 21}
    {$error sizeof(tacpi_madt_ht_pic) <> 21}
  {$endif}

  pacpi_madt_eio_pic = ^tacpi_madt_eio_pic;
  tacpi_madt_eio_pic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    cascade_vector: uacpi_u8;
    node: uacpi_u8;
    node_map: uacpi_u64;
  end;
  {$if sizeof(tacpi_madt_eio_pic) <> 13}
    {$error sizeof(tacpi_madt_eio_pic) <> 13}
  {$endif}

  pacpi_madt_msi_pic = ^tacpi_madt_msi_pic;
  tacpi_madt_msi_pic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    address: uacpi_u64;
    start: uacpi_u32;
    count: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_msi_pic) <> 19}
    {$error sizeof(tacpi_madt_msi_pic) <> 19}
  {$endif}

  pacpi_madt_bio_pic = ^tacpi_madt_bio_pic;
  tacpi_madt_bio_pic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    address: uacpi_u64;
    size: uacpi_u16;
    hardware_id: uacpi_u16;
    gsi_base: uacpi_u16;
  end;
  {$if sizeof(tacpi_madt_bio_pic) <> 17}
    {$error sizeof(tacpi_madt_bio_pic) <> 17}
  {$endif}

  pacpi_madt_lpc_pic = ^tacpi_madt_lpc_pic;
  tacpi_madt_lpc_pic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    address: uacpi_u64;
    size: uacpi_u16;
    cascade_vector: uacpi_u16;
  end;
  {$if sizeof(tacpi_madt_lpc_pic) <> 15}
    {$error sizeof(tacpi_madt_lpc_pic) <> 15}
  {$endif}

  pacpi_madt_rintc = ^tacpi_madt_rintc;
  tacpi_madt_rintc = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    rsvd: uacpi_u8;
    flags: uacpi_u32;
    hart_id: uacpi_u64;
    uid: uacpi_u32;
    ext_intc_id: uacpi_u32;
    address: uacpi_u64;
    size: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_rintc) <> 36}
    {$error sizeof(tacpi_madt_rintc) <> 36}
  {$endif}

  pacpi_madt_imsic = ^tacpi_madt_imsic;
  tacpi_madt_imsic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    rsvd: uacpi_u8;
    flags: uacpi_u32;
    num_ids: uacpi_u16;
    num_guest_ids: uacpi_u16;
    guest_index_bits: uacpi_u8;
    hart_index_bits: uacpi_u8;
    group_index_bits: uacpi_u8;
    group_index_shift: uacpi_u8;
  end;
  {$if sizeof(tacpi_madt_imsic) <> 16}
    {$error sizeof(tacpi_madt_imsic) <> 16}
  {$endif}

  pacpi_madt_aplic = ^tacpi_madt_aplic;
  tacpi_madt_aplic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    id: uacpi_u8;
    flags: uacpi_u32;
    hardware_id: uacpi_u64;
    idc_count: uacpi_u16;
    sources_count: uacpi_u16;
    gsi_base: uacpi_u32;
    address: uacpi_u64;
    size: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_aplic) <> 36}
    {$error sizeof(tacpi_madt_aplic) <> 36}
  {$endif}

  pacpi_madt_plic = ^tacpi_madt_plic;
  tacpi_madt_plic = packed record
    hdr: tacpi_entry_hdr;
    version: uacpi_u8;
    id: uacpi_u8;
    hardware_id: uacpi_u64;
    sources_count: uacpi_u16;
    max_priority: uacpi_u16;
    flags: uacpi_u32;
    size: uacpi_u32;
    address: uacpi_u64;
    gsi_base: uacpi_u32;
  end;
  {$if sizeof(tacpi_madt_plic) <> 36}
    {$error sizeof(tacpi_madt_plic) <> 36}
  {$endif}

  tacpi_srat_entry_type = (
    ACPI_SRAT_ENTRY_TYPE_PROCESSOR_AFFINITY = 0,
    ACPI_SRAT_ENTRY_TYPE_MEMORY_AFFINITY = 1,
    ACPI_SRAT_ENTRY_TYPE_X2APIC_AFFINITY = 2,
    ACPI_SRAT_ENTRY_TYPE_GICC_AFFINITY = 3,
    ACPI_SRAT_ENTRY_TYPE_GIC_ITS_AFFINITY = 4,
    ACPI_SRAT_ENTRY_TYPE_GENERIC_INITIATOR_AFFINITY = 5,
    ACPI_SRAT_ENTRY_TYPE_GENERIC_PORT_AFFINITY = 6,
    ACPI_SRAT_ENTRY_TYPE_RINTC_AFFINITY = 7
  );

  pacpi_srat = ^tacpi_srat;
  tacpi_srat = packed record
    hdr: tacpi_sdt_hdr;
    rsvd0: uacpi_u32;
    rsvd1: uacpi_u64;
    // start of tacpi_entry_hdr array
    entries: record end;
  end;
  {$if sizeof(tacpi_srat) <> 48}
    {$error sizeof(tacpi_srat) <> 48}
  {$endif}

const
  (*
   * tacpi_srat_processor_affinity->flags
   * tacpi_srat_x2apic_affinity->flags
   *)
  ACPI_SRAT_PROCESSOR_ENABLED = 1 shl 0;

type
  pacpi_srat_processor_affinity = ^tacpi_srat_processor_affinity;
  tacpi_srat_processor_affinity = packed record
    hdr: tacpi_entry_hdr;
    proximity_domain_low: uacpi_u8;
    id: uacpi_u8;
    flags: uacpi_u32;
    eid: uacpi_u8;
    proximity_domain_high: array [0..2] of uacpi_u8;
    clock_domain: uacpi_u32;
  end;
  {$if sizeof(tacpi_srat_processor_affinity) <> 16}
    {$error sizeof(tacpi_srat_processor_affinity) <> 16}
  {$endif}

const
  // tacpi_srat_memory_affinity->flags
  ACPI_SRAT_MEMORY_ENABLED = 1 shl 0;
  ACPI_SRAT_MEMORY_HOTPLUGGABLE = 1 shl 1;
  ACPI_SRAT_MEMORY_NON_VOLATILE = 1 shl 2;

type
  pacpi_srat_memory_affinity = ^tacpi_srat_memory_affinity;
  tacpi_srat_memory_affinity = packed record
    hdr: tacpi_entry_hdr;
    proximity_domain: uacpi_u32;
    rsvd0: uacpi_u16;
    address: uacpi_u64;
    length: uacpi_u64;
    rsvd1: uacpi_u32;
    flags: uacpi_u32;
    rsdv2: uacpi_u64;
  end;
  {$if sizeof(tacpi_srat_memory_affinity) <> 40}
    {$error sizeof(tacpi_srat_memory_affinity) <> 40}
  {$endif}

  pacpi_srat_x2apic_affinity = ^tacpi_srat_x2apic_affinity;
  tacpi_srat_x2apic_affinity = packed record
    hdr: tacpi_entry_hdr;
    rsvd0: uacpi_u16;
    proximity_domain: uacpi_u32;
    id: uacpi_u32;
    flags: uacpi_u32;
    clock_domain: uacpi_u32;
    rsvd1: uacpi_u32;
  end;
  {$if sizeof(tacpi_srat_x2apic_affinity) <> 24}
    {$error sizeof(tacpi_srat_x2apic_affinity) <> 24}
  {$endif}

const
  // tacpi_srat_gicc_affinity->flags
  ACPI_SRAT_GICC_ENABLED = 1 shl 0;

type
  pacpi_srat_gicc_affinity = ^tacpi_srat_gicc_affinity;
  tacpi_srat_gicc_affinity = packed record
    hdr: tacpi_entry_hdr;
    proximity_domain: uacpi_u32;
    uid: uacpi_u32;
    flags: uacpi_u32;
    clock_domain: uacpi_u32;
  end;
  {$if sizeof(tacpi_srat_gicc_affinity) <> 18}
    {$error sizeof(tacpi_srat_gicc_affinity) <> 18}
  {$endif}

  pacpi_srat_gic_its_affinity = ^tacpi_srat_gic_its_affinity;
  tacpi_srat_gic_its_affinity = packed record
    hdr: tacpi_entry_hdr;
    proximity_domain: uacpi_u32;
    rsvd: uacpi_u16;
    id: uacpi_u32;
  end;
  {$if sizeof(tacpi_srat_gic_its_affinity) <> 12}
    {$error sizeof(tacpi_srat_gic_its_affinity) <> 12}
  {$endif}

const
  // tacpi_srat_rintc_affinity->flags
  ACPI_GENERIC_AFFINITY_ENABLED = 1 shl 0;
  ACPI_GENERIC_AFFINITY_ARCH_TRANSACTIONS = 1 shl 1;

type
  pacpi_srat_generic_affinity = ^tacpi_srat_generic_affinity;
  tacpi_srat_generic_affinity = packed record
    hdr: tacpi_entry_hdr;
    rsvd0: uacpi_u8;
    handle_type: uacpi_u8;
    proximity_domain: uacpi_u32;
    handle: array [0..15] of uacpi_u8;
    flags: uacpi_u32;
    rsvd1: uacpi_u32;
  end;
  {$if sizeof(tacpi_srat_generic_affinity) <> 32}
    {$error sizeof(tacpi_srat_generic_affinity) <> 32}
  {$endif}

const
  // tacpi_srat_rintc_affinity->flags
  ACPI_SRAT_RINTC_AFFINITY_ENABLED = 1 shl 0;

type
  pacpi_srat_rintc_affinity = ^tacpi_srat_rintc_affinity;
  tacpi_srat_rintc_affinity = packed record
    hdr: tacpi_entry_hdr;
    rsvd: uacpi_u16;
    proximity_domain: uacpi_u32;
    uid: uacpi_u32;
    flags: uacpi_u32;
    clock_domain: uacpi_u32;
  end;
  {$if sizeof(tacpi_srat_rintc_affinity) <> 20}
    {$error sizeof(tacpi_srat_rintc_affinity) <> 20}
  {$endif}

  pacpi_slit = ^tacpi_slit;
  tacpi_slit = packed record
    hdr: tacpi_sdt_hdr;
    num_localities: uacpi_u64;
    // start of uacpi_u8 array
    matrix: record end;
  end;
  {$if sizeof(tacpi_slit) <> 44}
    {$error sizeof(tacpi_slit) <> 44}
  {$endif}

const
  (*
   * tacpi_gtdt->el*_flags
   * tacpi_gtdt_timer_entry->physical_flags
   * tacpi_gtdt_timer_entry->virtual_flags
   * tacpi_gtdt_watchdog->flags
   *)
  ACPI_GTDT_TRIGGERING = 1 shl 0;
  ACPI_GTDT_TRIGGERING_EDGE = 1;
  ACPI_GTDT_TRIGGERING_LEVEL = 0;

  (*
   * tacpi_gtdt->el*_flags
   * tacpi_gtdt_timer_entry->physical_flags
   * tacpi_gtdt_timer_entry->virtual_flags
   * tacpi_gtdt_watchdog->flags
   *)
  ACPI_GTDT_POLARITY = 1 shl 1;
  ACPI_GTDT_POLARITY_ACTIVE_LOW = 1;
  ACPI_GTDT_POLARITY_ACTIVE_HIGH = 0;

  // tacpi_gtdt->el*_flags
  ACPI_GTDT_ALWAYS_ON_CAPABLE = 1 shl 2;

type
  pacpi_gtdt = ^tacpi_gtdt;
  tacpi_gtdt = packed record
    hdr: tacpi_sdt_hdr;
    cnt_control_base: uacpi_u64;
    rsvd: uacpi_u32;
    el1_secure_gsiv: uacpi_u32;
    el1_secure_flags: uacpi_u32;
    el1_non_secure_gsiv: uacpi_u32;
    el1_non_secure_flags: uacpi_u32;
    el1_virtual_gsiv: uacpi_u32;
    el1_virtual_flags: uacpi_u32;
    el2_gsiv: uacpi_u32;
    el2_flags: uacpi_u32;
    cnt_read_base: uacpi_u64;
    platform_timer_count: uacpi_u32;
    platform_timer_offset: uacpi_u32;

    // revision >= 3
    el2_virtual_gsiv: uacpi_u32;
    el2_virtual_flags: uacpi_u32;
  end;
  {$if sizeof(tacpi_gtdt) <> 104}
    {$error sizeof(tacpi_gtdt) <> 104}
  {$endif}

  tacpi_gtdt_entry_type = (
    ACPI_GTDT_ENTRY_TYPE_TIMER = 0,
    ACPI_GTDT_ENTRY_TYPE_WATCHDOG = 1
  );

  pacpi_gtdt_entry_hdr = ^tacpi_gtdt_entry_hdr;
  tacpi_gtdt_entry_hdr = packed record
    &type: uacpi_u8;
    length: uacpi_u16;
  end;

  pacpi_gtdt_timer = ^tacpi_gtdt_timer;
  tacpi_gtdt_timer = packed record
    hdr: tacpi_gtdt_entry_hdr;
    rsvd: uacpi_u8;
    cnt_ctl_base: uacpi_u64;
    timer_count: uacpi_u32;
    timer_offset: uacpi_u32;
  end;
  {$if sizeof(tacpi_gtdt_timer) <> 20}
    {$error sizeof(tacpi_gtdt_timer) <> 20}
  {$endif}

const
  // tacpi_gtdt_timer_entry->common_flags
  ACPI_GTDT_TIMER_ENTRY_SECURE = 1 shl 0;
  ACPI_GTDT_TIMER_ENTRY_ALWAYS_ON_CAPABLE = 1 shl 1;

type
  pacpi_gtdt_timer_entry = ^tacpi_gtdt_timer_entry;
  tacpi_gtdt_timer_entry = packed record
    frame_number: uacpi_u8;
    rsvd: array [0..2] of uacpi_u8;
    cnt_base: uacpi_u64;
    el0_cnt_base: uacpi_u64;
    physical_gsiv: uacpi_u32;
    physical_flags: uacpi_u32;
    virtual_gsiv: uacpi_u32;
    virtual_flags: uacpi_u32;
    common_flags: uacpi_u32;
  end;
  {$if sizeof(tacpi_gtdt_timer_entry) <> 40}
    {$error sizeof(tacpi_gtdt_timer_entry) <> 40}
  {$endif}

const
  // tacpi_gtdt_watchdog->flags
  ACPI_GTDT_WATCHDOG_SECURE = 1 shl 2;

type
  pacpi_gtdt_watchdog = ^tacpi_gtdt_watchdog;
  tacpi_gtdt_watchdog = packed record
    hdr: tacpi_gtdt_entry_hdr;
    rsvd: uacpi_u8;
    refresh_frame: uacpi_u64;
    control_frame: uacpi_u64;
    gsiv: uacpi_u32;
    flags: uacpi_u32;
  end;
  {$if sizeof(tacpi_gtdt_watchdog) <> 28}
    {$error sizeof(tacpi_gtdt_watchdog) <> 28}
  {$endif}

const
  // tacpi_fdt->iapc_flags
  ACPI_IA_PC_LEGACY_DEVS = 1 shl 0;
  ACPI_IA_PC_8042 = 1 shl 1;
  ACPI_IA_PC_NO_VGA = 1 shl 2;
  ACPI_IA_PC_NO_MSI = 1 shl 3;
  ACPI_IA_PC_NO_PCIE_ASPM = 1 shl 4;
  ACPI_IA_PC_NO_CMOS_RTC = 1 shl 5;

  // tacpi_fdt->flags
  ACPI_WBINVD = 1 shl 0;
  ACPI_WBINVD_FLUSH = 1 shl 1;
  ACPI_PROC_C1 = 1 shl 2;
  ACPI_P_LVL2_UP = 1 shl 3;
  ACPI_PWR_BUTTON = 1 shl 4;
  ACPI_SLP_BUTTON = 1 shl 5;
  ACPI_FIX_RTC = 1 shl 6;
  ACPI_RTC_S4 = 1 shl 7;
  ACPI_TMR_VAL_EXT = 1 shl 8;
  ACPI_DCK_CAP = 1 shl 9;
  ACPI_RESET_REG_SUP = 1 shl 10;
  ACPI_SEALED_CASE = 1 shl 11;
  ACPI_HEADLESS = 1 shl 12;
  ACPI_CPU_SW_SLP = 1 shl 13;
  ACPI_PCI_EXP_WAK = 1 shl 14;
  ACPI_USE_PLATFORM_CLOCK = 1 shl 15;
  ACPI_S4_RTC_STS_VALID = 1 shl 16;
  ACPI_REMOTE_POWER_ON_CAPABLE = 1 shl 17;
  ACPI_FORCE_APIC_CLUSTER_MODEL = 1 shl 18;
  ACPI_FORCE_APIC_PHYS_DEST_MODE = 1 shl 19;
  ACPI_HW_REDUCED_ACPI = 1 shl 20;
  ACPI_LOW_POWER_S0_IDLE_CAPABLE = 1 shl 21;

  // tacpi_fdt->arm_flags
  ACPI_ARM_PSCI_COMPLIANT = 1 shl 0;
  ACPI_ARM_PSCI_USE_HVC = 1 shl 1;

type
  ppacpi_fadt = ^pacpi_fadt;
  pacpi_fadt = ^tacpi_fadt;
  tacpi_fadt = packed record
    hdr: tacpi_sdt_hdr;
    firmware_ctrl: uacpi_u32;
    dsdt: uacpi_u32;
    int_model: uacpi_u8;
    preferred_pm_profile: uacpi_u8;
    sci_int: uacpi_u16;
    smi_cmd: uacpi_u32;
    acpi_enable: uacpi_u8;
    acpi_disable: uacpi_u8;
    s4bios_req: uacpi_u8;
    pstate_cnt: uacpi_u8;
    pm1a_evt_blk: uacpi_u32;
    pm1b_evt_blk: uacpi_u32;
    pm1a_cnt_blk: uacpi_u32;
    pm1b_cnt_blk: uacpi_u32;
    pm2_cnt_blk: uacpi_u32;
    pm_tmr_blk: uacpi_u32;
    gpe0_blk: uacpi_u32;
    gpe1_blk: uacpi_u32;
    pm1_evt_len: uacpi_u8;
    pm1_cnt_len: uacpi_u8;
    pm2_cnt_len: uacpi_u8;
    pm_tmr_len: uacpi_u8;
    gpe0_blk_len: uacpi_u8;
    gpe1_blk_len: uacpi_u8;
    gpe1_base: uacpi_u8;
    cst_cnt: uacpi_u8;
    p_lvl2_lat: uacpi_u16;
    p_lvl3_lat: uacpi_u16;
    flush_size: uacpi_u16;
    flush_stride: uacpi_u16;
    duty_offset: uacpi_u8;
    duty_width: uacpi_u8;
    day_alrm: uacpi_u8;
    mon_alrm: uacpi_u8;
    century: uacpi_u8;
    iapc_boot_arch: uacpi_u16;
    rsvd: uacpi_u8;
    flags: uacpi_u32;
    reset_reg: tacpi_gas;
    reset_value: uacpi_u8;
    arm_boot_arch: uacpi_u16;
    fadt_minor_verison: uacpi_u8;
    x_firmware_ctrl: uacpi_u64;
    x_dsdt: uacpi_u64;
    x_pm1a_evt_blk: tacpi_gas;
    x_pm1b_evt_blk: tacpi_gas;
    x_pm1a_cnt_blk: tacpi_gas;
    x_pm1b_cnt_blk: tacpi_gas;
    x_pm2_cnt_blk: tacpi_gas;
    x_pm_tmr_blk: tacpi_gas;
    x_gpe0_blk: tacpi_gas;
    x_gpe1_blk: tacpi_gas;
    sleep_control_reg: tacpi_gas;
    sleep_status_reg: tacpi_gas;
    hypervisor_vendor_identity: uacpi_u64;
  end;
  {$if sizeof(tacpi_fadt) <> 276}
    {$error sizeof(tacpi_fadt) <> 276}
  {$endif}

const
  // tacpi_facs->flags
  ACPI_S4BIOS_F = 1 shl 0;
  ACPI_64BIT_WAKE_SUPPORTED_F = 1 shl 1;

  // tacpi_facs->ospm_flags
  ACPI_64BIT_WAKE_F = 1 shl 0;

type
  pacpi_facs = ^tacpi_facs;
  tacpi_facs = record
    signature: array [0..3] of uacpi_char;
    length: uacpi_u32;
    hardware_signature: uacpi_u32;
    firmware_waking_vector: uacpi_u32;
    global_lock: uacpi_u32;
    flags: uacpi_u32;
    x_firmware_waking_vector: uacpi_u64;
    version: uacpi_u8;
    rsvd0: array [0..2] of uacpi_char;
    ospm_flags: uacpi_u32;
    rsvd1: array [0..23] of uacpi_char;
  end;
  {$if sizeof(tacpi_facs) <> 64}
    {$error sizeof(tacpi_facs) <> 64}
  {$endif}

  pacpi_mcfg_allocation = ^tacpi_mcfg_allocation;
  tacpi_mcfg_allocation = packed record
    address: uacpi_u64;
    segment: uacpi_u16;
    start_bus: uacpi_u8;
    end_bus: uacpi_u8;
    rsvd: uacpi_u32;
  end;
  {$if sizeof(tacpi_mcfg_allocation) <> 16}
    {$error sizeof(tacpi_mcfg_allocation) <> 16}
  {$endif}

  pacpi_mcfg = ^tacpi_mcfg;
  tacpi_mcfg = packed record
    hdr: tacpi_sdt_hdr;
    rsvd: uacpi_u64;
    // start of tacpi_mcfg_allocation array
    entries: record end;
  end;
  {$if sizeof(tacpi_mcfg) <> 44}
    {$error sizeof(tacpi_mcfg) <> 44}
  {$endif}

const
  // tacpi_hpet->block_id
  ACPI_HPET_PCI_VENDOR_ID_SHIFT = 16;
  ACPI_HPET_LEGACY_REPLACEMENT_IRQ_ROUTING_CAPABLE = 1 shl 15;
  ACPI_HPET_COUNT_SIZE_CAP = 1 shl 13;
  ACPI_HPET_NUMBER_OF_COMPARATORS_SHIFT = 8;
  ACPI_HPET_NUMBER_OF_COMPARATORS_MASK = %11111;
  ACPI_HPET_HARDWARE_REV_ID_MASK = %11111111;

  // tacpi_hpet->flags
  ACPI_HPET_PAGE_PROTECTION_MASK = %11;
  ACPI_HPET_PAGE_NO_PROTECTION = 0;
  ACPI_HPET_PAGE_4K_PROTECTED = 1;
  ACPI_HPET_PAGE_64K_PROTECTED = 2;

type
  pacpi_hpet = ^tacpi_hpet;
  tacpi_hpet = packed record
    hdr: tacpi_sdt_hdr;
    block_id: uacpi_u32;
    address: tacpi_gas;
    number: uacpi_u8;
    min_clock_tick: uacpi_u16;
    flags: uacpi_u8;
  end;
  {$if sizeof(tacpi_hpet) <> 56}
    {$error sizeof(tacpi_hpet) <> 56}
  {$endif}

const
// PM1{a,b}_STS
  ACPI_PM1_STS_TMR_STS_IDX = 0;
  ACPI_PM1_STS_BM_STS_IDX = 4;
  ACPI_PM1_STS_GBL_STS_IDX = 5;
  ACPI_PM1_STS_PWRBTN_STS_IDX = 8;
  ACPI_PM1_STS_SLPBTN_STS_IDX = 9;
  ACPI_PM1_STS_RTC_STS_IDX = 10;
  ACPI_PM1_STS_IGN0_IDX = 11;
  ACPI_PM1_STS_PCIEXP_WAKE_STS_IDX = 14;
  ACPI_PM1_STS_WAKE_STS_IDX = 15;
  ACPI_PM1_STS_TMR_STS_MASK = 1 shl ACPI_PM1_STS_TMR_STS_IDX;
  ACPI_PM1_STS_BM_STS_MASK = 1 shl ACPI_PM1_STS_BM_STS_IDX;
  ACPI_PM1_STS_GBL_STS_MASK = 1 shl ACPI_PM1_STS_GBL_STS_IDX;
  ACPI_PM1_STS_PWRBTN_STS_MASK = 1 shl ACPI_PM1_STS_PWRBTN_STS_IDX;
  ACPI_PM1_STS_SLPBTN_STS_MASK = 1 shl ACPI_PM1_STS_SLPBTN_STS_IDX;
  ACPI_PM1_STS_RTC_STS_MASK = 1 shl ACPI_PM1_STS_RTC_STS_IDX;
  ACPI_PM1_STS_IGN0_MASK = 1 shl ACPI_PM1_STS_IGN0_IDX;
  ACPI_PM1_STS_PCIEXP_WAKE_STS_MASK = 1 shl ACPI_PM1_STS_PCIEXP_WAKE_STS_IDX;
  ACPI_PM1_STS_WAKE_STS_MASK = 1 shl ACPI_PM1_STS_WAKE_STS_IDX;
  ACPI_PM1_STS_CLEAR = 1;

  // PM1{a,b}_EN
  ACPI_PM1_EN_TMR_EN_IDX = 0;
  ACPI_PM1_EN_GBL_EN_IDX = 5;
  ACPI_PM1_EN_PWRBTN_EN_IDX = 8;
  ACPI_PM1_EN_SLPBTN_EN_IDX = 9;
  ACPI_PM1_EN_RTC_EN_IDX = 10;
  ACPI_PM1_EN_PCIEXP_WAKE_DIS_IDX = 14;
  ACPI_PM1_EN_TMR_EN_MASK = 1 shl ACPI_PM1_EN_TMR_EN_IDX;
  ACPI_PM1_EN_GBL_EN_MASK = 1 shl ACPI_PM1_EN_GBL_EN_IDX;
  ACPI_PM1_EN_PWRBTN_EN_MASK = 1 shl ACPI_PM1_EN_PWRBTN_EN_IDX;
  ACPI_PM1_EN_SLPBTN_EN_MASK = 1 shl ACPI_PM1_EN_SLPBTN_EN_IDX;
  ACPI_PM1_EN_RTC_EN_MASK = 1 shl ACPI_PM1_EN_RTC_EN_IDX;
  ACPI_PM1_EN_PCIEXP_WAKE_DIS_MASK = 1 shl ACPI_PM1_EN_PCIEXP_WAKE_DIS_IDX;

  // PM1{a,b}_CNT_BLK
  ACPI_PM1_CNT_SCI_EN_IDX = 0;
  ACPI_PM1_CNT_BM_RLD_IDX = 1;
  ACPI_PM1_CNT_GBL_RLS_IDX = 2;
  ACPI_PM1_CNT_RSVD0_IDX = 3;
  ACPI_PM1_CNT_RSVD1_IDX = 4;
  ACPI_PM1_CNT_RSVD2_IDX = 5;
  ACPI_PM1_CNT_RSVD3_IDX = 6;
  ACPI_PM1_CNT_RSVD4_IDX = 7;
  ACPI_PM1_CNT_RSVD5_IDX = 8;
  ACPI_PM1_CNT_IGN0_IDX = 9;
  ACPI_PM1_CNT_SLP_TYP_IDX = 10;
  ACPI_PM1_CNT_SLP_EN_IDX = 13;
  ACPI_PM1_CNT_RSVD6_IDX = 14;
  ACPI_PM1_CNT_RSVD7_IDX = 15;

  ACPI_SLP_TYP_MAX = $7;

  ACPI_PM1_CNT_SCI_EN_MASK = 1 shl ACPI_PM1_CNT_SCI_EN_IDX;
  ACPI_PM1_CNT_BM_RLD_MASK = 1 shl ACPI_PM1_CNT_BM_RLD_IDX;
  ACPI_PM1_CNT_GBL_RLS_MASK = 1 shl ACPI_PM1_CNT_GBL_RLS_IDX;
  ACPI_PM1_CNT_SLP_TYP_MASK = ACPI_SLP_TYP_MAX shl ACPI_PM1_CNT_SLP_TYP_IDX;
  ACPI_PM1_CNT_SLP_EN_MASK = 1 shl ACPI_PM1_CNT_SLP_EN_IDX;

  (*
   * SCI_EN is not in this mask even though the spec says it must be preserved.
   * This is because it's known to be bugged on some hardware that relies on
   * software writing 1 to it after resume (as indicated by a similar comment in
   * ACPICA)
   *)
  ACPI_PM1_CNT_PRESERVE_MASK = (
    (1 shl ACPI_PM1_CNT_RSVD0_IDX) or
    (1 shl ACPI_PM1_CNT_RSVD1_IDX) or
    (1 shl ACPI_PM1_CNT_RSVD2_IDX) or
    (1 shl ACPI_PM1_CNT_RSVD3_IDX) or
    (1 shl ACPI_PM1_CNT_RSVD4_IDX) or
    (1 shl ACPI_PM1_CNT_RSVD5_IDX) or
    (1 shl ACPI_PM1_CNT_IGN0_IDX) or
    (1 shl ACPI_PM1_CNT_RSVD6_IDX) or
    (1 shl ACPI_PM1_CNT_RSVD7_IDX)
  );

  // PM2_CNT
  ACPI_PM2_CNT_ARB_DIS_IDX = 0;
  ACPI_PM2_CNT_ARB_DIS_MASK = 1 shl ACPI_PM2_CNT_ARB_DIS_IDX;

  // All bits are reserved but this first one
  ACPI_PM2_CNT_PRESERVE_MASK = not uacpi_u64(ACPI_PM2_CNT_ARB_DIS_MASK);

  // SLEEP_CONTROL_REG
  ACPI_SLP_CNT_RSVD0_IDX = 0;
  ACPI_SLP_CNT_IGN0_IDX = 1;
  ACPI_SLP_CNT_SLP_TYP_IDX = 2;
  ACPI_SLP_CNT_SLP_EN_IDX = 5;
  ACPI_SLP_CNT_RSVD1_IDX = 6;
  ACPI_SLP_CNT_RSVD2_IDX = 7;

  ACPI_SLP_CNT_SLP_TYP_MASK = ACPI_SLP_TYP_MAX shl ACPI_SLP_CNT_SLP_TYP_IDX;
  ACPI_SLP_CNT_SLP_EN_MASK = 1 shl ACPI_SLP_CNT_SLP_EN_IDX;

  ACPI_SLP_CNT_PRESERVE_MASK = (
    (1 shl ACPI_SLP_CNT_RSVD0_IDX) or
    (1 shl ACPI_SLP_CNT_IGN0_IDX) or
    (1 shl ACPI_SLP_CNT_RSVD1_IDX) or
    (1 shl ACPI_SLP_CNT_RSVD2_IDX)
  );

  ACPI_SLP_STS_WAK_STS_IDX = 7;

  ACPI_SLP_STS_WAK_STS_MASK = 1 shl ACPI_SLP_STS_WAK_STS_IDX;

  { All bits are reserved but this last one }
  ACPI_SLP_STS_PRESERVE_MASK = not uacpi_u64(ACPI_SLP_STS_WAK_STS_MASK);

  ACPI_SLP_STS_CLEAR = 1;

type
  pacpi_dsdt = ^tacpi_dsdt;
  tacpi_dsdt = packed record
    hdr: tacpi_sdt_hdr;
    definition_block: array of uacpi_u8;
  end;

  pacpi_ssdt = ^tacpi_ssdt;
  tacpi_ssdt = packed record
    hdr: tacpi_sdt_hdr;
    definition_block: array of uacpi_u8;
  end;

const
  (*
   * ACPI 6.5 specification:
   * Bit [0] - Set if the device is present.
   * Bit [1] - Set if the device is enabled and decoding its resources.
   * Bit [2] - Set if the device should be shown in the UI.
   * Bit [3] - Set if the device is functioning properly (cleared if device
   *           failed its diagnostics).
   * Bit [4] - Set if the battery is present.
   *)
  ACPI_STA_RESULT_DEVICE_PRESENT = 1 shl 0;
  ACPI_STA_RESULT_DEVICE_ENABLED = 1 shl 1;
  ACPI_STA_RESULT_DEVICE_SHOWN_IN_UI = 1 shl 2;
  ACPI_STA_RESULT_DEVICE_FUNCTIONING = 1 shl 3;
  ACPI_STA_RESULT_DEVICE_BATTERY_PRESENT = 1 shl 4;

  ACPI_REG_DISCONNECT = 0;
  ACPI_REG_CONNECT = 1;

type
  pacpi_ecdt = ^tacpi_ecdt;
  tacpi_ecdt = packed record
    hdr: tacpi_sdt_hdr;
    ec_control: tacpi_gas;
    ec_data: tacpi_gas;
    uid: uacpi_u32;
    gpe_bit: uacpi_u8;
    // start of uacpi_char array
    ec_id: record end;
  end;
  {$if sizeof(tacpi_ecdt) <> 65}
    {$error sizeof(tacpi_ecdt) <> 65}
  {$endif}

  // tacpi_dbg2_device_info->port_type
  tacpi_dbg2_type = (
    ACPI_DBG2_TYPE_SERIAL = $8000,
    ACPI_DBG2_TYPE_1394 = $8001,
    ACPI_DBG2_TYPE_USB = $8002,
    ACPI_DBG2_TYPE_NET = $8003
  );

  (*
   * Constants for:
   * - tacpi_dbg2_device_info->port_subtype
   *   if tacpi_dbg2_device_info->port_type == ACPI_DBG2_TYPE_SERIAL.
   * - tacpi_spcr->interface_type (there is no type/subtype distinction in SPCR).
   *)
  tacpi_dbg2_serial_subtype = (
    ACPI_DBG2_SUBTYPE_SERIAL_NS16550 = $0,
    ACPI_DBG2_SUBTYPE_SERIAL_NS16550_DBGP1 = $1,
    ACPI_DBG2_SUBTYPE_SERIAL_MAX311XE_SPI = $2,
    ACPI_DBG2_SUBTYPE_SERIAL_PL011 = $3,
    ACPI_DBG2_SUBTYPE_SERIAL_MSM8X60 = $4,
    ACPI_DBG2_SUBTYPE_SERIAL_NS16550_NVIDIA = $5,
    ACPI_DBG2_SUBTYPE_SERIAL_TI_OMAP = $6,
    ACPI_DBG2_SUBTYPE_SERIAL_APM88XXXX = $8,
    ACPI_DBG2_SUBTYPE_SERIAL_MSM8974 = $9,
    ACPI_DBG2_SUBTYPE_SERIAL_SAM5250 = $A,
    ACPI_DBG2_SUBTYPE_SERIAL_INTEL_USIF = $B,
    ACPI_DBG2_SUBTYPE_SERIAL_IMX6 = $C,
    ACPI_DBG2_SUBTYPE_SERIAL_ARM_SBSA_32BIT = $D,
    ACPI_DBG2_SUBTYPE_SERIAL_ARM_SBSA_GENERIC = $E,
    ACPI_DBG2_SUBTYPE_SERIAL_ARM_DCC = $F,
    ACPI_DBG2_SUBTYPE_SERIAL_BCM2835 = $10,
    ACPI_DBG2_SUBTYPE_SERIAL_SDM845_1_8432MHZ = $11,
    ACPI_DBG2_SUBTYPE_SERIAL_NS16550_GAS = $12,
    ACPI_DBG2_SUBTYPE_SERIAL_SDM845_7_372MHZ = $13,
    ACPI_DBG2_SUBTYPE_SERIAL_INTEL_LPSS = $14,
    ACPI_DBG2_SUBTYPE_SERIAL_RISCV_SBI = $15
  );

  (*
   * Constants for tacpi_dbg2_device_info->port_subtype
   * if tacpi_dbg2_device_info->port_type == ACPI_DBG2_TYPE_1394.
   *)
  tacpi_dbg2_1394_subtype = (
    ACPI_DBG2_SUBTYPE_1394_STANDARD = $0
  );

  (*
   * Constants for tacpi_dbg2_device_info->port_subtype
   * if tacpi_dbg2_device_info->port_type == ACPI_DBG2_TYPE_USB.
   *)
  tacpi_dbg2_usb_subtype = (
    ACPI_DBG2_SUBTYPE_USB_XHCI_DEBUG = $0,
    ACPI_DBG2_SUBTYPE_USB_EHCI_DEBUG = $1
  );

  pacpi_dbg2 = ^tacpi_dbg2;
  tacpi_dbg2 = packed record
    hdr: tacpi_sdt_hdr;
    offset_dbg_device_info: uacpi_u32;
    number_dbg_device_info: uacpi_u32;
    (*
     *  Variable length fields below:
     *  At ->offset_dbg_device_info:
     *    struct tacpi_dbg2_dbg_device_info dbg_devices[number_dbg_device_info];
     *)
  end;
  {$if sizeof(tacpi_dbg2) <> 44}
    {$error sizeof(tacpi_dbg2) <> 44}
  {$endif}

  pacpi_dbg2_dbg_device_info = ^tacpi_dbg2_dbg_device_info;
  tacpi_dbg2_dbg_device_info = packed record
    revision: uacpi_u8;
    length: uacpi_u16;
    number_generic_address_registers: uacpi_u8;
    namespace_string_length: uacpi_u16;
    namespace_string_offset: uacpi_u16;
    oem_data_length: uacpi_u16;
    oem_data_offset: uacpi_u16;
    port_type: uacpi_u16;
    port_subtype: uacpi_u16;
    rsvd: uacpi_u16;
    base_address_register_offset: uacpi_u16;
    address_size_offset: uacpi_u16;
    (*
     * Variable length fields below:
     * At ->base_address_register_offset:
     *     struct tacpi_gas base_address_register[number_generic_address_registers];
     * At ->address_size_offset
     *     u32 address_size[number_generic_address_registers];
     * At ->namespace_string_offset:
     *     char namespace_string[namespace_string_length];
     * At ->oem_data_offset:
     *     char oem_data[oem_data_length];
     *)
  end;
  {$if sizeof(tacpi_dbg2_dbg_device_info) <> 22}
    {$error sizeof(tacpi_dbg2_dbg_device_info) <> 22}
  {$endif}

const
  // tacpi_scpr->interrupt_type
  ACPI_SPCR_INTERRUPT_TYPE_8259 = $1;
  ACPI_SPCR_INTERRUPT_TYPE_IOAPIC = $2;
  ACPI_SPCR_INTERRUPT_TYPE_IOSAPIC = $4;
  ACPI_SPCR_INTERRUPT_TYPE_GIC = $8;
  ACPI_SPCR_INTERRUPT_TYPE_PLIC_APLIC = $10;

  // tacpi_spcr->pci_flags
  ACPI_SPCR_PCI_FLAGS_DO_NOT_DISABLE = $1;

type
  // tacpi_spcr->terminal_type
  tacpi_spcr_terminal_type = (
    ACPI_SPCR_TERMINAL_TYPE_VT100 = 0,
    ACPI_SPCR_TERMINAL_TYPE_EXTENDED_VT100 = 1,
    ACPI_SPCR_TERMINAL_TYPE_VT_UTF8 = 2,
    ACPI_SPCR_TERMINAL_TYPE_ANSI = 3
  );

  pacpi_spcr = ^tacpi_spcr;
  tacpi_spcr = packed record
    hdr: tacpi_sdt_hdr;
    interface_type: uacpi_u8;
    rsvd: array [0..2] of uacpi_u8;
    base_address: tacpi_gas;
    interrupt_type: uacpi_u8;
    irq: uacpi_u8;
    gsi: uacpi_u32;
    configured_baud_rate: uacpi_u8;
    parity: uacpi_u8;
    stop_bits: uacpi_u8;
    flow_control: uacpi_u8;
    terminal_type: uacpi_u8;
    language: uacpi_u8;
    pci_device_id: uacpi_u16;
    pci_vendor_id: uacpi_u16;
    pci_bus_number: uacpi_u8;
    pci_device_number: uacpi_u8;
    pci_function_number: uacpi_u8;
    pci_flags: uacpi_u32;
    pci_segment: uacpi_u8;
    uart_clock_frequency: uacpi_u32;
    precise_baud_rate: uacpi_u32;
    namespace_string_length: uacpi_u16;
    namespace_string_offset: uacpi_u16;
    (*
     * At ->namespace_string_offset:
     *    char namespace_string[namespace_string_length];
     *)
  end;
  {$if sizeof(tacpi_spcr) <> 88}
    {$error sizeof(tacpi_spcr) <> 88}
  {$endif}

  pacpi_rhct_hdr = ^tacpi_rhct_hdr;
  tacpi_rhct_hdr = packed record
    &type: uacpi_u16;
    length: uacpi_u16;
    revision: uacpi_u16;
  end;
  {$if sizeof(tacpi_rhct_hdr) <> 6}
    {$error sizeof(tacpi_rhct_hdr) <> 6}
  {$endif}

const
  // tacpi_rhct->flags
  ACPI_TIMER_CANNOT_WAKE_CPU = 1 shl 0;

type
  pacpi_rhct = ^tacpi_rhct;
  tacpi_rhct = packed record
    hdr: tacpi_sdt_hdr;
    flags: uacpi_u32;
    timebase_frequency: uacpi_u64;
    node_count: uacpi_u32;
    nodes_offset: uacpi_u32;
    // start of tacpi_rhct_hdr array
    entries: record end;
  end;
  {$if sizeof(tacpi_rhct) <> 56}
    {$error sizeof(tacpi_rhct) <> 56}
  {$endif}

  tacpi_rhct_entry_type = (
    ACPI_RHCT_ENTRY_TYPE_ISA_STRING = 0,
    ACPI_RHCT_ENTRY_TYPE_CMO = 1,
    ACPI_RHCT_ENTRY_TYPE_MMU = 2,
    ACPI_RHCT_ENTRY_TYPE_HART_INFO = 65535
  );

  pacpi_rhct_isa_string = ^tacpi_rhct_isa_string;
  tacpi_rhct_isa_string = packed record
    hdr: tacpi_rhct_hdr;
    length: uacpi_u16;
    // start of uacpi_u8 array
    isa: record end;
  end;
  {$if sizeof(tacpi_rhct_isa_string) <> 8}
    {$error sizeof(tacpi_rhct_isa_string) <> 8}
  {$endif}

  pacpi_rhct_cmo = ^tacpi_rhct_cmo;
  tacpi_rhct_cmo = packed record
    hdr: tacpi_rhct_hdr;
    rsvd: uacpi_u8;
    cbom_size: uacpi_u8;
    cbop_size: uacpi_u8;
    cboz_size: uacpi_u8;
  end;
  {$if sizeof(tacpi_rhct_cmo) <> 10}
    {$error sizeof(tacpi_rhct_cmo) <> 10}
  {$endif}

  tacpi_rhct_mmu_type = (
    ACPI_RHCT_MMU_TYPE_SV39 = 0,
    ACPI_RHCT_MMU_TYPE_SV48 = 1,
    ACPI_RHCT_MMU_TYPE_SV57 = 2
  );

  pacpi_rhct_mmu = ^tacpi_rhct_mmu;
  tacpi_rhct_mmu = packed record
    hdr: tacpi_rhct_hdr;
    rsvd: uacpi_u8;
    &type: uacpi_u8;
  end;
  {$if sizeof(tacpi_rhct_mmu) <> 8}
    {$error sizeof(tacpi_rhct_mmu) <> 8}
  {$endif}

  pacpi_rhct_hart_info = ^tacpi_rhct_hart_info;
  tacpi_rhct_hart_info = packed record
    hdr: tacpi_rhct_hdr;
    offset_count: uacpi_u16;
    uid: uacpi_u32;
    // start of uacpi_u32 array
    offsets: record end;
  end;
  {$if sizeof(tacpi_rhct_hart_info) <> 12}
    {$error sizeof(tacpi_rhct_hart_info) <> 12}
  {$endif}

const
  ACPI_LARGE_ITEM = 1 shl 7;
  ACPI_SMALL_ITEM_NAME_IDX = 3;
  ACPI_SMALL_ITEM_NAME_MASK = $F;
  ACPI_SMALL_ITEM_LENGTH_MASK = $7;
  ACPI_LARGE_ITEM_NAME_MASK = $7F;

  // Small items
  ACPI_RESOURCE_IRQ = $04;
  ACPI_RESOURCE_DMA = $05;
  ACPI_RESOURCE_START_DEPENDENT = $06;
  ACPI_RESOURCE_END_DEPENDENT = $07;
  ACPI_RESOURCE_IO = $08;
  ACPI_RESOURCE_FIXED_IO = $09;
  ACPI_RESOURCE_FIXED_DMA = $0A;
  ACPI_RESOURCE_VENDOR_TYPE0 = $0E;
  ACPI_RESOURCE_END_TAG = $0F;

  // Large items
  ACPI_RESOURCE_MEMORY24 = $01;
  ACPI_RESOURCE_GENERIC_REGISTER = $02;
  ACPI_RESOURCE_VENDOR_TYPE1 = $04;
  ACPI_RESOURCE_MEMORY32 = $05;
  ACPI_RESOURCE_FIXED_MEMORY32 = $06;
  ACPI_RESOURCE_ADDRESS32 = $07;
  ACPI_RESOURCE_ADDRESS16 = $08;
  ACPI_RESOURCE_EXTENDED_IRQ = $09;
  ACPI_RESOURCE_ADDRESS64 = $0A;
  ACPI_RESOURCE_ADDRESS64_EXTENDED = $0B;
  ACPI_RESOURCE_GPIO_CONNECTION = $0C;
  ACPI_RESOURCE_PIN_FUNCTION = $0D;
  ACPI_RESOURCE_SERIAL_CONNECTION = $0E;
  ACPI_RESOURCE_PIN_CONFIGURATION = $0F;
  ACPI_RESOURCE_PIN_GROUP = $10;
  ACPI_RESOURCE_PIN_GROUP_FUNCTION = $11;
  ACPI_RESOURCE_PIN_GROUP_CONFIGURATION = $12;
  ACPI_RESOURCE_CLOCK_INPUT = $13;

type
  (*
   * Resources as encoded by the raw AML byte stream.
   * For decode API & human usable structures refer to uacpi/resources.h
   *)
  tacpi_small_item = packed record
    type_and_length: uacpi_u8;
  end;
  {$if sizeof(tacpi_small_item) <> 1}
    {$error sizeof(tacpi_small_item) <> 1}
  {$endif}

  tacpi_resource_irq = packed record
    common: tacpi_small_item;
    irq_mask: uacpi_u16;
    flags: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_irq) <> 4}
    {$error sizeof(tacpi_resource_irq) <> 4}
  {$endif}

  tacpi_resource_dma = packed record
    common: tacpi_small_item;
    channel_mask: uacpi_u8;
    flags: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_dma) <> 3}
    {$error sizeof(tacpi_resource_dma) <> 3}
  {$endif}

  tacpi_resource_start_dependent = packed record
    common: tacpi_small_item;
    flags: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_start_dependent) <> 2}
    {$error sizeof(tacpi_resource_start_dependent) <> 2}
  {$endif}

  tacpi_resource_end_dependent = packed record
    common: tacpi_small_item;
  end;
  {$if sizeof(tacpi_resource_end_dependent) <> 1}
    {$error sizeof(tacpi_resource_end_dependent) <> 1}
  {$endif}

  tacpi_resource_io = packed record
    common: tacpi_small_item;
    information: uacpi_u8;
    minimum: uacpi_u16;
    maximum: uacpi_u16;
    alignment: uacpi_u8;
    length: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_io) <> 8}
    {$error sizeof(tacpi_resource_io) <> 8}
  {$endif}

  tacpi_resource_fixed_io = packed record
    common: tacpi_small_item;
    address: uacpi_u16;
    length: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_fixed_io) <> 4}
    {$error sizeof(tacpi_resource_fixed_io) <> 4}
  {$endif}

  tacpi_resource_fixed_dma = packed record
    common: tacpi_small_item;
    request_line: uacpi_u16;
    channel: uacpi_u16;
    transfer_width: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_fixed_dma) <> 6}
    {$error sizeof(tacpi_resource_fixed_dma) <> 6}
  {$endif}

  tacpi_resource_vendor_defined_type0 = packed record
    common: tacpi_small_item;
    // start of uacpi_u8 array
    byte_data: record end;
  end;
  {$if sizeof(tacpi_resource_vendor_defined_type0) <> 1}
    {$error sizeof(tacpi_resource_vendor_defined_type0) <> 1}
  {$endif}

  tacpi_resource_end_tag = packed record
    common: tacpi_small_item;
    checksum: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_end_tag) <> 2}
    {$error sizeof(tacpi_resource_end_tag) <> 2}
  {$endif}

  tacpi_large_item = packed record
    &type: uacpi_u8;
    length: uacpi_u16;
  end;
  {$if sizeof(tacpi_large_item) <> 3}
    {$error sizeof(tacpi_large_item) <> 3}
  {$endif}

  tacpi_resource_memory24 = packed record
    common: tacpi_large_item;
    information: uacpi_u8;
    minimum: uacpi_u16;
    maximum: uacpi_u16;
    alignment: uacpi_u16;
    length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_memory24) <> 12}
    {$error sizeof(tacpi_resource_memory24) <> 12}
  {$endif}

  tacpi_resource_vendor_defined_type1 = packed record
    common: tacpi_large_item;
    // start of uacpi_u8 array
    byte_data: record end;
  end;
  {$if sizeof(tacpi_resource_vendor_defined_type1) <> 3}
    {$error sizeof(tacpi_resource_vendor_defined_type1) <> 3}
  {$endif}

  tacpi_resource_memory32 = packed record
    common: tacpi_large_item;
    information: uacpi_u8;
    minimum: uacpi_u32;
    maximum: uacpi_u32;
    alignment: uacpi_u32;
    length: uacpi_u32;
  end;
  {$if sizeof(tacpi_resource_memory32) <> 20}
    {$error sizeof(tacpi_resource_memory32) <> 20}
  {$endif}

  tacpi_resource_fixed_memory32 = packed record
    common: tacpi_large_item;
    information: uacpi_u8;
    address: uacpi_u32;
    length: uacpi_u32;
  end;
  {$if sizeof(tacpi_resource_fixed_memory32) <> 12}
    {$error sizeof(tacpi_resource_fixed_memory32) <> 12}
  {$endif}

  tacpi_resource_address = packed record
    common: tacpi_large_item;
    &type: uacpi_u8;
    flags: uacpi_u8;
    type_flags: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_address) <> 6}
    {$error sizeof(tacpi_resource_address) <> 6}
  {$endif}

  tacpi_resource_address64 = packed record
    common: tacpi_resource_address;
    granularity: uacpi_u64;
    minimum: uacpi_u64;
    maximum: uacpi_u64;
    translation_offset: uacpi_u64;
    length: uacpi_u64;
  end;
  {$if sizeof(tacpi_resource_address64) <> 46}
    {$error sizeof(tacpi_resource_address64) <> 46}
  {$endif}

  tacpi_resource_address32 = packed record
    common: tacpi_resource_address;
    granularity: uacpi_u32;
    minimum: uacpi_u32;
    maximum: uacpi_u32;
    translation_offset: uacpi_u32;
    length: uacpi_u32;
  end;
  {$if sizeof(tacpi_resource_address32) <> 26}
    {$error sizeof(tacpi_resource_address32) <> 26}
  {$endif}

  tacpi_resource_address16 = packed record
    common: tacpi_resource_address;
    granularity: uacpi_u16;
    minimum: uacpi_u16;
    maximum: uacpi_u16;
    translation_offset: uacpi_u16;
    length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_address16) <> 16}
    {$error sizeof(tacpi_resource_address16) <> 16}
  {$endif}

  tacpi_resource_address64_extended = packed record
    common: tacpi_resource_address;
    revision_id: uacpi_u8;
    rsvd: uacpi_u8;
    granularity: uacpi_u64;
    minimum: uacpi_u64;
    maximum: uacpi_u64;
    translation_offset: uacpi_u64;
    length: uacpi_u64;
    attributes: uacpi_u64;
  end;
  {$if sizeof(tacpi_resource_address64_extended) <> 56}
    {$error sizeof(tacpi_resource_address64_extended) <> 56}
  {$endif}

  tacpi_resource_extended_irq = packed record
    common: tacpi_large_item;
    flags: uacpi_u8;
    num_irqs: uacpi_u8;
    // start of uacpi_u32 array
    irqs: record end;
  end;
  {$if sizeof(tacpi_resource_extended_irq) <> 5}
    {$error sizeof(tacpi_resource_extended_irq) <> 5}
  {$endif}

  tacpi_resource_generic_register = packed record
    common: tacpi_large_item;
    address_space_id: uacpi_u8;
    bit_width: uacpi_u8;
    bit_offset: uacpi_u8;
    access_size: uacpi_u8;
    address: uacpi_u64;
  end;
  {$if sizeof(tacpi_resource_generic_register) <> 15}
    {$error sizeof(tacpi_resource_generic_register) <> 15}
  {$endif}

  tacpi_resource_gpio_connection = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    &type: uacpi_u8;
    general_flags: uacpi_u16;
    connection_flags: uacpi_u16;
    pull_configuration: uacpi_u8;
    drive_strength: uacpi_u16;
    debounce_timeout: uacpi_u16;
    pin_table_offset: uacpi_u16;
    source_index: uacpi_u8;
    source_offset: uacpi_u16;
    vendor_data_offset: uacpi_u16;
    vendor_data_length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_gpio_connection) <> 23}
    {$error sizeof(tacpi_resource_gpio_connection) <> 23}
  {$endif}

const
  ACPI_SERIAL_TYPE_I2C = 1;
  ACPI_SERIAL_TYPE_SPI = 2;
  ACPI_SERIAL_TYPE_UART = 3;
  ACPI_SERIAL_TYPE_CSI2 = 4;
  ACPI_SERIAL_TYPE_MAX = ACPI_SERIAL_TYPE_CSI2;

type
  tacpi_resource_serial = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    source_index: uacpi_u8;
    &type: uacpi_u8;
    flags: uacpi_u8;
    type_specific_flags: uacpi_u16;
    type_specific_revision_id: uacpi_u8;
    type_data_length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_serial) <> 12}
    {$error sizeof(tacpi_resource_serial) <> 12}
  {$endif}

  tacpi_resource_serial_i2c = packed record
    common: tacpi_resource_serial;
    connection_speed: uacpi_u32;
    slave_address: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_serial_i2c) <> 18}
    {$error sizeof(tacpi_resource_serial_i2c) <> 18}
  {$endif}

  tacpi_resource_serial_spi = packed record
    common: tacpi_resource_serial;
    connection_speed: uacpi_u32;
    data_bit_length: uacpi_u8;
    phase: uacpi_u8;
    polarity: uacpi_u8;
    device_selection: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_serial_spi) <> 21}
    {$error sizeof(tacpi_resource_serial_spi) <> 21}
  {$endif}

  tacpi_resource_serial_uart = packed record
    common: tacpi_resource_serial;
    baud_rate: uacpi_u32;
    rx_fifo: uacpi_u16;
    tx_fifo: uacpi_u16;
    parity: uacpi_u8;
    lines_enabled: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_serial_uart) <> 22}
    {$error sizeof(tacpi_resource_serial_uart) <> 22}
  {$endif}

  tacpi_resource_serial_csi2 = packed record
    common: tacpi_resource_serial;
  end;
  {$if sizeof(tacpi_resource_serial_csi2) <> 12}
    {$error sizeof(tacpi_resource_serial_csi2) <> 12}
  {$endif}

  tacpi_resource_pin_function = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    flags: uacpi_u16;
    pull_configuration: uacpi_u8;
    function_number: uacpi_u16;
    pin_table_offset: uacpi_u16;
    source_index: uacpi_u8;
    source_offset: uacpi_u16;
    vendor_data_offset: uacpi_u16;
    vendor_data_length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_pin_function) <> 18}
    {$error sizeof(tacpi_resource_pin_function) <> 18}
  {$endif}

  tacpi_resource_pin_configuration = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    flags: uacpi_u16;
    &type: uacpi_u8;
    value: uacpi_u32;
    pin_table_offset: uacpi_u16;
    source_index: uacpi_u8;
    source_offset: uacpi_u16;
    vendor_data_offset: uacpi_u16;
    vendor_data_length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_pin_configuration) <> 20}
    {$error sizeof(tacpi_resource_pin_configuration) <> 20}
  {$endif}

  tacpi_resource_pin_group = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    flags: uacpi_u16;
    pin_table_offset: uacpi_u16;
    source_lable_offset: uacpi_u16;
    vendor_data_offset: uacpi_u16;
    vendor_data_length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_pin_group) <> 14}
    {$error sizeof(tacpi_resource_pin_group) <> 14}
  {$endif}

  tacpi_resource_pin_group_function = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    flags: uacpi_u16;
    _function: uacpi_u16;
    source_index: uacpi_u8;
    source_offset: uacpi_u16;
    source_lable_offset: uacpi_u16;
    vendor_data_offset: uacpi_u16;
    vendor_data_length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_pin_group_function) <> 17}
    {$error sizeof(tacpi_resource_pin_group_function) <> 17}
  {$endif}

  tacpi_resource_pin_group_configuration = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    flags: uacpi_u16;
    &type: uacpi_u8;
    value: uacpi_u32;
    source_index: uacpi_u8;
    source_offset: uacpi_u16;
    source_lable_offset: uacpi_u16;
    vendor_data_offset: uacpi_u16;
    vendor_data_length: uacpi_u16;
  end;
  {$if sizeof(tacpi_resource_pin_group_configuration) <> 20}
    {$error sizeof(tacpi_resource_pin_group_configuration) <> 20}
  {$endif}

  tacpi_resource_clock_input = packed record
    common: tacpi_large_item;
    revision_id: uacpi_u8;
    flags: uacpi_u16;
    divisor: uacpi_u16;
    numerator: uacpi_u32;
    source_index: uacpi_u8;
  end;
  {$if sizeof(tacpi_resource_clock_input) <> 13}
    {$error sizeof(tacpi_resource_clock_input) <> 13}
  {$endif}
