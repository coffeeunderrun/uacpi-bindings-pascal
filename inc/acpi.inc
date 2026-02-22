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
  Pacpi_gas = ^Tacpi_gas;
  Tacpi_gas = packed record
    address_space_id: Tuacpi_u8;
    register_bit_width: Tuacpi_u8;
    register_bit_offset: Tuacpi_u8;
    access_size: Tuacpi_u8;
    address: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_gas) <> 12}
    {$error sizeof(Tacpi_gas) <> 12}
  {$endif}

  Pacpi_rsdp = ^Tacpi_rsdp;
  Tacpi_rsdp = packed record
    signature: array [0..7] of Tuacpi_char;
    checksum: Tuacpi_u8;
    oemid: array [0..5] of Tuacpi_char;
    revision: Tuacpi_u8;
    rsdt_addr: Tuacpi_u32;

    { vvvv available if .revision >= 2.0 only }
    length: Tuacpi_u32;
    xsdt_addr: Tuacpi_u64;
    extended_checksum: Tuacpi_u8;
    rsvd: array [0..2] of Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_rsdp) <> 36}
    {$error sizeof(Tacpi_rsdp) <> 36}
  {$endif}

  Pacpi_sdt_hdr = ^Tacpi_sdt_hdr;
  Tacpi_sdt_hdr = packed record
    signature: array [0..3] of Tuacpi_char;
    length: Tuacpi_u32;
    revision: Tuacpi_u8;
    checksum: Tuacpi_u8;
    oemid: array [0..5] of Tuacpi_char;
    oem_table_id: array [0..7] of Tuacpi_char;
    oem_revision: Tuacpi_u32;
    creator_id: Tuacpi_u32;
    creator_revision: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_sdt_hdr) <> 36}
    {$error sizeof(Tacpi_sdt_hdr) <> 36}
  {$endif}

  Pacpi_rsdt = ^Tacpi_rsdt;
  Tacpi_rsdt = packed record
    hdr: Tacpi_sdt_hdr;
    entries: record end;
  end;

  Pacpi_xsdt = ^Tacpi_xsdt;
  Tacpi_xsdt = packed record
    hdr: Tacpi_sdt_hdr;
    entries: record end;
  end;

  Pacpi_entry_hdr = ^Tacpi_entry_hdr;
  Tacpi_entry_hdr = packed record
    (*
     * - Tacpi_madt_entry_type for the APIC table
     * - Tacpi_srat_entry_type for the SRAT table
     *)
    &type: Tuacpi_u8;
    length: Tuacpi_u8;
  end;

const
  // Tacpi_madt->flags
  ACPI_PCAT_COMPAT = 1 shl 0;

type
  Tacpi_madt_entry_type = (
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

  Pacpi_madt = ^Tacpi_madt;
  Tacpi_madt = packed record
    hdr: Tacpi_sdt_hdr;
    local_interrupt_controller_address: Tuacpi_u32;
    flags: Tuacpi_u32;
    // start of Tacpi_entry_hdr array
    entries: record end;
  end;
  {$if sizeof(Tacpi_madt) <> 44}
    {$error sizeof(Tacpi_madt) <> 44}
  {$endif}

const
  (*
   * - Tacpi_madt_lapic->flags
   * - Tacpi_madt_lsapic->flags
   * - Tacpi_madt_x2apic->flags
   *)
  ACPI_PIC_ENABLED = 1 shl 0;
  ACPI_PIC_ONLINE_CAPABLE = 1 shl 1;

type
  Pacpi_madt_lapic = ^Tacpi_madt_lapic;
  Tacpi_madt_lapic = packed record
    hdr: Tacpi_entry_hdr;
    uid: Tuacpi_u8;
    id: Tuacpi_u8;
    flags: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_lapic) <> 8}
    {$error sizeof(Tacpi_madt_lapic) <> 8}
  {$endif}

  Pacpi_madt_ioapic = ^Tacpi_madt_ioapic;
  Tacpi_madt_ioapic = packed record
    hdr: Tacpi_entry_hdr;
    id: Tuacpi_u8;
    rsvd: Tuacpi_u8;
    address: Tuacpi_u32;
    gsi_base: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_ioapic) <> 12}
    {$error sizeof(Tacpi_madt_ioapic) <> 12}
  {$endif}

const
  (*
   * - Tacpi_madt_interrupt_source_override->flags
   * - Tacpi_madt_nmi_source->flags
   * - Tacpi_madt_lapic_nmi->flags
   * - Tacpi_madt_platform_interrupt_source->flags
   * - Tacpi_madt_x2apic_nmi->flags
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
  Pacpi_madt_interrupt_source_override = ^Tacpi_madt_interrupt_source_override;
  Tacpi_madt_interrupt_source_override = packed record
    hdr: Tacpi_entry_hdr;
    bus: Tuacpi_u8;
    source: Tuacpi_u8;
    gsi: Tuacpi_u32;
    flags: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_madt_interrupt_source_override) <> 10}
    {$error sizeof(Tacpi_madt_interrupt_source_override) <> 10}
  {$endif}

  Pacpi_madt_nmi_source = ^Tacpi_madt_nmi_source;
  Tacpi_madt_nmi_source = packed record
    hdr: Tacpi_entry_hdr;
    flags: Tuacpi_u16;
    gsi: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_nmi_source) <> 8}
    {$error sizeof(Tacpi_madt_nmi_source) <> 8}
  {$endif}

  Pacpi_madt_lapic_nmi = ^Tacpi_madt_lapic_nmi;
  Tacpi_madt_lapic_nmi = packed record
    hdr: Tacpi_entry_hdr;
    uid: Tuacpi_u8;
    flags: Tuacpi_u16;
    lint: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_madt_lapic_nmi) <> 6}
    {$error sizeof(Tacpi_madt_lapic_nmi) <> 6}
  {$endif}

  Tacpi_madt_lapic_address_override = packed record
    hdr: Tacpi_entry_hdr;
    rsvd: Tuacpi_u16;
    address: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_madt_lapic_address_override) <> 12}
    {$error sizeof(Tacpi_madt_lapic_address_override) <> 12}
  {$endif}

  Pacpi_madt_iosapic = ^Tacpi_madt_iosapic;
  Tacpi_madt_iosapic = packed record
    hdr: Tacpi_entry_hdr;
    id: Tuacpi_u8;
    rsvd: Tuacpi_u8;
    gsi_base: Tuacpi_u32;
    address: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_madt_iosapic) <> 16}
    {$error sizeof(Tacpi_madt_iosapic) <> 16}
  {$endif}

  Pacpi_madt_lsapic = ^Tacpi_madt_lsapic;
  Tacpi_madt_lsapic = packed record
    hdr: Tacpi_entry_hdr;
    acpi_id: Tuacpi_u8;
    id: Tuacpi_u8;
    eid: Tuacpi_u8;
    reserved: array [0..2] of Tuacpi_u8;
    flags: Tuacpi_u32;
    uid: Tuacpi_u32;
    // start of Tuacpi_char array
    uid_string: record end;
  end;
  {$if sizeof(Tacpi_madt_lsapic) <> 16}
    {$error sizeof(Tacpi_madt_lsapic) <> 16}
  {$endif}

const
  // Tacpi_madt_platform_interrupt_source->platform_flags
  ACPI_CPEI_PROCESSOR_OVERRIDE = 1 shl 0;

type
  Pacpi_madt_platform_interrupt_source = ^Tacpi_madt_platform_interrupt_source;
  Tacpi_madt_platform_interrupt_source = packed record
    hdr: Tacpi_entry_hdr;
    flags: Tuacpi_u16;
    &type: Tuacpi_u8;
    processor_id: Tuacpi_u8;
    processor_eid: Tuacpi_u8;
    iosapic_vector: Tuacpi_u8;
    gsi: Tuacpi_u32;
    platform_flags: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_platform_interrupt_source) <> 16}
    {$error sizeof(Tacpi_madt_platform_interrupt_source) <> 16}
  {$endif}

  Pacpi_madt_x2apic = ^Tacpi_madt_x2apic;
  Tacpi_madt_x2apic = packed record
    hdr: Tacpi_entry_hdr;
    rsvd: Tuacpi_u16;
    id: Tuacpi_u32;
    flags: Tuacpi_u32;
    uid: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_x2apic) <> 16}
    {$error sizeof(Tacpi_madt_x2apic) <> 16}
  {$endif}

  Pacpi_madt_x2apic_nmi = ^Tacpi_madt_x2apic_nmi;
  Tacpi_madt_x2apic_nmi = packed record
    hdr: Tacpi_entry_hdr;
    flags: Tuacpi_u16;
    uid: Tuacpi_u32;
    lint: Tuacpi_u8;
    reserved: array [0..2] of Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_madt_x2apic_nmi) <> 12}
    {$error sizeof(Tacpi_madt_x2apic_nmi) <> 12}
  {$endif}

const
  // Tacpi_madt_gicc->flags
  ACPI_GICC_ENABLED = 1 shl 0;
  ACPI_GICC_PERF_INTERRUPT_MODE = 1 shl 1;
  ACPI_GICC_VGIC_MAINTENANCE_INTERRUPT_MODE = 1 shl 2;
  ACPI_GICC_ONLINE_CAPABLE = 1 shl 3;

  // ACPI_GICC_*_INTERRUPT_MODE
  ACPI_GICC_TRIGGERING_EDGE = 1;
  ACPI_GICC_TRIGGERING_LEVEL = 0;

type
  Pacpi_madt_gicc = ^Tacpi_madt_gicc;
  Tacpi_madt_gicc = packed record
    hdr: Tacpi_entry_hdr;
    rsvd0: Tuacpi_u16;
    interface_number: Tuacpi_u32;
    acpi_id: Tuacpi_u32;
    flags: Tuacpi_u32;
    parking_protocol_version: Tuacpi_u32;
    perf_interrupt_gsiv: Tuacpi_u32;
    parked_address: Tuacpi_u64;
    address: Tuacpi_u64;
    gicv: Tuacpi_u64;
    gich: Tuacpi_u64;
    vgic_maitenante_interrupt: Tuacpi_u32;
    gicr_base_address: Tuacpi_u64;
    mpidr: Tuacpi_u64;
    power_efficiency_class: Tuacpi_u8;
    rsvd1: Tuacpi_u8;
    spe_overflow_interrupt: Tuacpi_u16;
    trbe_interrupt: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_madt_gicc) <> 82}
    {$error sizeof(Tacpi_madt_gicc) <> 82}
  {$endif}

  Pacpi_madt_gicd = ^Tacpi_madt_gicd;
  Tacpi_madt_gicd = packed record
    hdr: Tacpi_entry_hdr;
    rsvd0: Tuacpi_u16;
    id: Tuacpi_u32;
    address: Tuacpi_u64;
    system_vector_base: Tuacpi_u32;
    gic_version: Tuacpi_u8;
    reserved1: array [0..2] of Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_madt_gicd) <> 24}
    {$error sizeof(Tacpi_madt_gicd) <> 24}
  {$endif}

const
  // Tacpi_madt_gic_msi_frame->flags
  ACPI_SPI_SELECT = 1 shl 0;

type
  Pacpi_madt_gic_msi_frame = ^Tacpi_madt_gic_msi_frame;
  Tacpi_madt_gic_msi_frame = packed record
    hdr: Tacpi_entry_hdr;
    rsvd: Tuacpi_u16;
    id: Tuacpi_u32;
    address: Tuacpi_u64;
    flags: Tuacpi_u32;
    spi_count: Tuacpi_u16;
    spi_base: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_madt_gic_msi_frame) <> 24}
    {$error sizeof(Tacpi_madt_gic_msi_frame) <> 24}
  {$endif}

  Pacpi_madt_gicr = ^Tacpi_madt_gicr;
  Tacpi_madt_gicr = packed record
    hdr: Tacpi_entry_hdr;
    rsvd: Tuacpi_u16;
    address: Tuacpi_u64;
    length: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_gicr) <> 16}
    {$error sizeof(Tacpi_madt_gicr) <> 16}
  {$endif}

  Pacpi_madt_gic_its = ^Tacpi_madt_gic_its;
  Tacpi_madt_gic_its = packed record
    hdr: Tacpi_entry_hdr;
    rsvd0: Tuacpi_u16;
    id: Tuacpi_u32;
    address: Tuacpi_u64;
    rsvd1: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_gic_its) <> 20}
    {$error sizeof(Tacpi_madt_gic_its) <> 20}
  {$endif}

  Pacpi_madt_multiprocessor_wakeup = ^Tacpi_madt_multiprocessor_wakeup;
  Tacpi_madt_multiprocessor_wakeup = packed record
    hdr: Tacpi_entry_hdr;
    mailbox_version: Tuacpi_u16;
    rsvd: Tuacpi_u32;
    mailbox_address: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_madt_multiprocessor_wakeup) <> 16}
    {$error sizeof(Tacpi_madt_multiprocessor_wakeup) <> 16}
  {$endif}

const
  ACPI_CORE_PIC_ENABLED = 1 shl 0;

type
  Pacpi_madt_core_pic = ^Tacpi_madt_core_pic;
  Tacpi_madt_core_pic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    acpi_id: Tuacpi_u32;
    id: Tuacpi_u32;
    flags: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_core_pic) <> 15}
    {$error sizeof(Tacpi_madt_core_pic) <> 15}
  {$endif}

  Pacpi_madt_lio_pic = ^Tacpi_madt_lio_pic;
  Tacpi_madt_lio_pic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    address: Tuacpi_u64;
    size: Tuacpi_u16;
    cascade_vector: Tuacpi_u16;
    cascade_vector_mapping: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_madt_lio_pic) <> 23}
    {$error sizeof(Tacpi_madt_lio_pic) <> 23}
  {$endif}

  Pacpi_madt_ht_pic = ^Tacpi_madt_ht_pic;
  Tacpi_madt_ht_pic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    address: Tuacpi_u64;
    size: Tuacpi_u16;
    cascade_vector: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_madt_ht_pic) <> 21}
    {$error sizeof(Tacpi_madt_ht_pic) <> 21}
  {$endif}

  Pacpi_madt_eio_pic = ^Tacpi_madt_eio_pic;
  Tacpi_madt_eio_pic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    cascade_vector: Tuacpi_u8;
    node: Tuacpi_u8;
    node_map: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_madt_eio_pic) <> 13}
    {$error sizeof(Tacpi_madt_eio_pic) <> 13}
  {$endif}

  Pacpi_madt_msi_pic = ^Tacpi_madt_msi_pic;
  Tacpi_madt_msi_pic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    address: Tuacpi_u64;
    start: Tuacpi_u32;
    count: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_msi_pic) <> 19}
    {$error sizeof(Tacpi_madt_msi_pic) <> 19}
  {$endif}

  Pacpi_madt_bio_pic = ^Tacpi_madt_bio_pic;
  Tacpi_madt_bio_pic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    address: Tuacpi_u64;
    size: Tuacpi_u16;
    hardware_id: Tuacpi_u16;
    gsi_base: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_madt_bio_pic) <> 17}
    {$error sizeof(Tacpi_madt_bio_pic) <> 17}
  {$endif}

  Pacpi_madt_lpc_pic = ^Tacpi_madt_lpc_pic;
  Tacpi_madt_lpc_pic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    address: Tuacpi_u64;
    size: Tuacpi_u16;
    cascade_vector: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_madt_lpc_pic) <> 15}
    {$error sizeof(Tacpi_madt_lpc_pic) <> 15}
  {$endif}

  Pacpi_madt_rintc = ^Tacpi_madt_rintc;
  Tacpi_madt_rintc = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    rsvd: Tuacpi_u8;
    flags: Tuacpi_u32;
    hart_id: Tuacpi_u64;
    uid: Tuacpi_u32;
    ext_intc_id: Tuacpi_u32;
    address: Tuacpi_u64;
    size: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_rintc) <> 36}
    {$error sizeof(Tacpi_madt_rintc) <> 36}
  {$endif}

  Pacpi_madt_imsic = ^Tacpi_madt_imsic;
  Tacpi_madt_imsic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    rsvd: Tuacpi_u8;
    flags: Tuacpi_u32;
    num_ids: Tuacpi_u16;
    num_guest_ids: Tuacpi_u16;
    guest_index_bits: Tuacpi_u8;
    hart_index_bits: Tuacpi_u8;
    group_index_bits: Tuacpi_u8;
    group_index_shift: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_madt_imsic) <> 16}
    {$error sizeof(Tacpi_madt_imsic) <> 16}
  {$endif}

  Pacpi_madt_aplic = ^Tacpi_madt_aplic;
  Tacpi_madt_aplic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    id: Tuacpi_u8;
    flags: Tuacpi_u32;
    hardware_id: Tuacpi_u64;
    idc_count: Tuacpi_u16;
    sources_count: Tuacpi_u16;
    gsi_base: Tuacpi_u32;
    address: Tuacpi_u64;
    size: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_aplic) <> 36}
    {$error sizeof(Tacpi_madt_aplic) <> 36}
  {$endif}

  Pacpi_madt_plic = ^Tacpi_madt_plic;
  Tacpi_madt_plic = packed record
    hdr: Tacpi_entry_hdr;
    version: Tuacpi_u8;
    id: Tuacpi_u8;
    hardware_id: Tuacpi_u64;
    sources_count: Tuacpi_u16;
    max_priority: Tuacpi_u16;
    flags: Tuacpi_u32;
    size: Tuacpi_u32;
    address: Tuacpi_u64;
    gsi_base: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_madt_plic) <> 36}
    {$error sizeof(Tacpi_madt_plic) <> 36}
  {$endif}

  Tacpi_srat_entry_type = (
    ACPI_SRAT_ENTRY_TYPE_PROCESSOR_AFFINITY = 0,
    ACPI_SRAT_ENTRY_TYPE_MEMORY_AFFINITY = 1,
    ACPI_SRAT_ENTRY_TYPE_X2APIC_AFFINITY = 2,
    ACPI_SRAT_ENTRY_TYPE_GICC_AFFINITY = 3,
    ACPI_SRAT_ENTRY_TYPE_GIC_ITS_AFFINITY = 4,
    ACPI_SRAT_ENTRY_TYPE_GENERIC_INITIATOR_AFFINITY = 5,
    ACPI_SRAT_ENTRY_TYPE_GENERIC_PORT_AFFINITY = 6,
    ACPI_SRAT_ENTRY_TYPE_RINTC_AFFINITY = 7
  );

  Pacpi_srat = ^Tacpi_srat;
  Tacpi_srat = packed record
    hdr: Tacpi_sdt_hdr;
    rsvd0: Tuacpi_u32;
    rsvd1: Tuacpi_u64;
    // start of Tacpi_entry_hdr array
    entries: record end;
  end;
  {$if sizeof(Tacpi_srat) <> 48}
    {$error sizeof(Tacpi_srat) <> 48}
  {$endif}

const
  (*
   * Tacpi_srat_processor_affinity->flags
   * Tacpi_srat_x2apic_affinity->flags
   *)
  ACPI_SRAT_PROCESSOR_ENABLED = 1 shl 0;

type
  Pacpi_srat_processor_affinity = ^Tacpi_srat_processor_affinity;
  Tacpi_srat_processor_affinity = packed record
    hdr: Tacpi_entry_hdr;
    proximity_domain_low: Tuacpi_u8;
    id: Tuacpi_u8;
    flags: Tuacpi_u32;
    eid: Tuacpi_u8;
    proximity_domain_high: array [0..2] of Tuacpi_u8;
    clock_domain: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_srat_processor_affinity) <> 16}
    {$error sizeof(Tacpi_srat_processor_affinity) <> 16}
  {$endif}

const
  // Tacpi_srat_memory_affinity->flags
  ACPI_SRAT_MEMORY_ENABLED = 1 shl 0;
  ACPI_SRAT_MEMORY_HOTPLUGGABLE = 1 shl 1;
  ACPI_SRAT_MEMORY_NON_VOLATILE = 1 shl 2;

type
  Pacpi_srat_memory_affinity = ^Tacpi_srat_memory_affinity;
  Tacpi_srat_memory_affinity = packed record
    hdr: Tacpi_entry_hdr;
    proximity_domain: Tuacpi_u32;
    rsvd0: Tuacpi_u16;
    address: Tuacpi_u64;
    length: Tuacpi_u64;
    rsvd1: Tuacpi_u32;
    flags: Tuacpi_u32;
    rsdv2: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_srat_memory_affinity) <> 40}
    {$error sizeof(Tacpi_srat_memory_affinity) <> 40}
  {$endif}

  Pacpi_srat_x2apic_affinity = ^Tacpi_srat_x2apic_affinity;
  Tacpi_srat_x2apic_affinity = packed record
    hdr: Tacpi_entry_hdr;
    rsvd0: Tuacpi_u16;
    proximity_domain: Tuacpi_u32;
    id: Tuacpi_u32;
    flags: Tuacpi_u32;
    clock_domain: Tuacpi_u32;
    rsvd1: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_srat_x2apic_affinity) <> 24}
    {$error sizeof(Tacpi_srat_x2apic_affinity) <> 24}
  {$endif}

const
  // Tacpi_srat_gicc_affinity->flags
  ACPI_SRAT_GICC_ENABLED = 1 shl 0;

type
  Pacpi_srat_gicc_affinity = ^Tacpi_srat_gicc_affinity;
  Tacpi_srat_gicc_affinity = packed record
    hdr: Tacpi_entry_hdr;
    proximity_domain: Tuacpi_u32;
    uid: Tuacpi_u32;
    flags: Tuacpi_u32;
    clock_domain: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_srat_gicc_affinity) <> 18}
    {$error sizeof(Tacpi_srat_gicc_affinity) <> 18}
  {$endif}

  Pacpi_srat_gic_its_affinity = ^Tacpi_srat_gic_its_affinity;
  Tacpi_srat_gic_its_affinity = packed record
    hdr: Tacpi_entry_hdr;
    proximity_domain: Tuacpi_u32;
    rsvd: Tuacpi_u16;
    id: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_srat_gic_its_affinity) <> 12}
    {$error sizeof(Tacpi_srat_gic_its_affinity) <> 12}
  {$endif}

const
  // Tacpi_srat_rintc_affinity->flags
  ACPI_GENERIC_AFFINITY_ENABLED = 1 shl 0;
  ACPI_GENERIC_AFFINITY_ARCH_TRANSACTIONS = 1 shl 1;

type
  Pacpi_srat_generic_affinity = ^Tacpi_srat_generic_affinity;
  Tacpi_srat_generic_affinity = packed record
    hdr: Tacpi_entry_hdr;
    rsvd0: Tuacpi_u8;
    handle_type: Tuacpi_u8;
    proximity_domain: Tuacpi_u32;
    handle: array [0..15] of Tuacpi_u8;
    flags: Tuacpi_u32;
    rsvd1: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_srat_generic_affinity) <> 32}
    {$error sizeof(Tacpi_srat_generic_affinity) <> 32}
  {$endif}

const
  // Tacpi_srat_rintc_affinity->flags
  ACPI_SRAT_RINTC_AFFINITY_ENABLED = 1 shl 0;

type
  Pacpi_srat_rintc_affinity = ^Tacpi_srat_rintc_affinity;
  Tacpi_srat_rintc_affinity = packed record
    hdr: Tacpi_entry_hdr;
    rsvd: Tuacpi_u16;
    proximity_domain: Tuacpi_u32;
    uid: Tuacpi_u32;
    flags: Tuacpi_u32;
    clock_domain: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_srat_rintc_affinity) <> 20}
    {$error sizeof(Tacpi_srat_rintc_affinity) <> 20}
  {$endif}

  Pacpi_slit = ^Tacpi_slit;
  Tacpi_slit = packed record
    hdr: Tacpi_sdt_hdr;
    num_localities: Tuacpi_u64;
    // start of Tuacpi_u8 array
    matrix: record end;
  end;
  {$if sizeof(Tacpi_slit) <> 44}
    {$error sizeof(Tacpi_slit) <> 44}
  {$endif}

const
  (*
   * Tacpi_gtdt->el*_flags
   * Tacpi_gtdt_timer_entry->physical_flags
   * Tacpi_gtdt_timer_entry->virtual_flags
   * Tacpi_gtdt_watchdog->flags
   *)
  ACPI_GTDT_TRIGGERING = 1 shl 0;
  ACPI_GTDT_TRIGGERING_EDGE = 1;
  ACPI_GTDT_TRIGGERING_LEVEL = 0;

  (*
   * Tacpi_gtdt->el*_flags
   * Tacpi_gtdt_timer_entry->physical_flags
   * Tacpi_gtdt_timer_entry->virtual_flags
   * Tacpi_gtdt_watchdog->flags
   *)
  ACPI_GTDT_POLARITY = 1 shl 1;
  ACPI_GTDT_POLARITY_ACTIVE_LOW = 1;
  ACPI_GTDT_POLARITY_ACTIVE_HIGH = 0;

  // Tacpi_gtdt->el*_flags
  ACPI_GTDT_ALWAYS_ON_CAPABLE = 1 shl 2;

type
  Pacpi_gtdt = ^Tacpi_gtdt;
  Tacpi_gtdt = packed record
    hdr: Tacpi_sdt_hdr;
    cnt_control_base: Tuacpi_u64;
    rsvd: Tuacpi_u32;
    el1_secure_gsiv: Tuacpi_u32;
    el1_secure_flags: Tuacpi_u32;
    el1_non_secure_gsiv: Tuacpi_u32;
    el1_non_secure_flags: Tuacpi_u32;
    el1_virtual_gsiv: Tuacpi_u32;
    el1_virtual_flags: Tuacpi_u32;
    el2_gsiv: Tuacpi_u32;
    el2_flags: Tuacpi_u32;
    cnt_read_base: Tuacpi_u64;
    platform_timer_count: Tuacpi_u32;
    platform_timer_offset: Tuacpi_u32;

    // revision >= 3
    el2_virtual_gsiv: Tuacpi_u32;
    el2_virtual_flags: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_gtdt) <> 104}
    {$error sizeof(Tacpi_gtdt) <> 104}
  {$endif}

  Tacpi_gtdt_entry_type = (
    ACPI_GTDT_ENTRY_TYPE_TIMER = 0,
    ACPI_GTDT_ENTRY_TYPE_WATCHDOG = 1
  );

  Pacpi_gtdt_entry_hdr = ^Tacpi_gtdt_entry_hdr;
  Tacpi_gtdt_entry_hdr = packed record
    &type: Tuacpi_u8;
    length: Tuacpi_u16;
  end;

  Pacpi_gtdt_timer = ^Tacpi_gtdt_timer;
  Tacpi_gtdt_timer = packed record
    hdr: Tacpi_gtdt_entry_hdr;
    rsvd: Tuacpi_u8;
    cnt_ctl_base: Tuacpi_u64;
    timer_count: Tuacpi_u32;
    timer_offset: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_gtdt_timer) <> 20}
    {$error sizeof(Tacpi_gtdt_timer) <> 20}
  {$endif}

const
  // Tacpi_gtdt_timer_entry->common_flags
  ACPI_GTDT_TIMER_ENTRY_SECURE = 1 shl 0;
  ACPI_GTDT_TIMER_ENTRY_ALWAYS_ON_CAPABLE = 1 shl 1;

type
  Pacpi_gtdt_timer_entry = ^Tacpi_gtdt_timer_entry;
  Tacpi_gtdt_timer_entry = packed record
    frame_number: Tuacpi_u8;
    rsvd: array [0..2] of Tuacpi_u8;
    cnt_base: Tuacpi_u64;
    el0_cnt_base: Tuacpi_u64;
    physical_gsiv: Tuacpi_u32;
    physical_flags: Tuacpi_u32;
    virtual_gsiv: Tuacpi_u32;
    virtual_flags: Tuacpi_u32;
    common_flags: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_gtdt_timer_entry) <> 40}
    {$error sizeof(Tacpi_gtdt_timer_entry) <> 40}
  {$endif}

const
  // Tacpi_gtdt_watchdog->flags
  ACPI_GTDT_WATCHDOG_SECURE = 1 shl 2;

type
  Pacpi_gtdt_watchdog = ^Tacpi_gtdt_watchdog;
  Tacpi_gtdt_watchdog = packed record
    hdr: Tacpi_gtdt_entry_hdr;
    rsvd: Tuacpi_u8;
    refresh_frame: Tuacpi_u64;
    control_frame: Tuacpi_u64;
    gsiv: Tuacpi_u32;
    flags: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_gtdt_watchdog) <> 28}
    {$error sizeof(Tacpi_gtdt_watchdog) <> 28}
  {$endif}

const
  // Tacpi_fdt->iapc_flags
  ACPI_IA_PC_LEGACY_DEVS = 1 shl 0;
  ACPI_IA_PC_8042 = 1 shl 1;
  ACPI_IA_PC_NO_VGA = 1 shl 2;
  ACPI_IA_PC_NO_MSI = 1 shl 3;
  ACPI_IA_PC_NO_PCIE_ASPM = 1 shl 4;
  ACPI_IA_PC_NO_CMOS_RTC = 1 shl 5;

  // Tacpi_fdt->flags
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

  // Tacpi_fdt->arm_flags
  ACPI_ARM_PSCI_COMPLIANT = 1 shl 0;
  ACPI_ARM_PSCI_USE_HVC = 1 shl 1;

type
  Pacpi_fadt = ^Tacpi_fadt;
  Tacpi_fadt = packed record
    hdr: Tacpi_sdt_hdr;
    firmware_ctrl: Tuacpi_u32;
    dsdt: Tuacpi_u32;
    int_model: Tuacpi_u8;
    preferred_pm_profile: Tuacpi_u8;
    sci_int: Tuacpi_u16;
    smi_cmd: Tuacpi_u32;
    acpi_enable: Tuacpi_u8;
    acpi_disable: Tuacpi_u8;
    s4bios_req: Tuacpi_u8;
    pstate_cnt: Tuacpi_u8;
    pm1a_evt_blk: Tuacpi_u32;
    pm1b_evt_blk: Tuacpi_u32;
    pm1a_cnt_blk: Tuacpi_u32;
    pm1b_cnt_blk: Tuacpi_u32;
    pm2_cnt_blk: Tuacpi_u32;
    pm_tmr_blk: Tuacpi_u32;
    gpe0_blk: Tuacpi_u32;
    gpe1_blk: Tuacpi_u32;
    pm1_evt_len: Tuacpi_u8;
    pm1_cnt_len: Tuacpi_u8;
    pm2_cnt_len: Tuacpi_u8;
    pm_tmr_len: Tuacpi_u8;
    gpe0_blk_len: Tuacpi_u8;
    gpe1_blk_len: Tuacpi_u8;
    gpe1_base: Tuacpi_u8;
    cst_cnt: Tuacpi_u8;
    p_lvl2_lat: Tuacpi_u16;
    p_lvl3_lat: Tuacpi_u16;
    flush_size: Tuacpi_u16;
    flush_stride: Tuacpi_u16;
    duty_offset: Tuacpi_u8;
    duty_width: Tuacpi_u8;
    day_alrm: Tuacpi_u8;
    mon_alrm: Tuacpi_u8;
    century: Tuacpi_u8;
    iapc_boot_arch: Tuacpi_u16;
    rsvd: Tuacpi_u8;
    flags: Tuacpi_u32;
    reset_reg: Tacpi_gas;
    reset_value: Tuacpi_u8;
    arm_boot_arch: Tuacpi_u16;
    fadt_minor_verison: Tuacpi_u8;
    x_firmware_ctrl: Tuacpi_u64;
    x_dsdt: Tuacpi_u64;
    x_pm1a_evt_blk: Tacpi_gas;
    x_pm1b_evt_blk: Tacpi_gas;
    x_pm1a_cnt_blk: Tacpi_gas;
    x_pm1b_cnt_blk: Tacpi_gas;
    x_pm2_cnt_blk: Tacpi_gas;
    x_pm_tmr_blk: Tacpi_gas;
    x_gpe0_blk: Tacpi_gas;
    x_gpe1_blk: Tacpi_gas;
    sleep_control_reg: Tacpi_gas;
    sleep_status_reg: Tacpi_gas;
    hypervisor_vendor_identity: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_fadt) <> 276}
    {$error sizeof(Tacpi_fadt) <> 276}
  {$endif}

const
  // Tacpi_facs->flags
  ACPI_S4BIOS_F = 1 shl 0;
  ACPI_64BIT_WAKE_SUPPORTED_F = 1 shl 1;

  // Tacpi_facs->ospm_flags
  ACPI_64BIT_WAKE_F = 1 shl 0;

type
  Pacpi_facs = ^Tacpi_facs;
  Tacpi_facs = record
    signature: array [0..3] of Tuacpi_char;
    length: Tuacpi_u32;
    hardware_signature: Tuacpi_u32;
    firmware_waking_vector: Tuacpi_u32;
    global_lock: Tuacpi_u32;
    flags: Tuacpi_u32;
    x_firmware_waking_vector: Tuacpi_u64;
    version: Tuacpi_u8;
    rsvd0: array [0..2] of Tuacpi_char;
    ospm_flags: Tuacpi_u32;
    rsvd1: array [0..23] of Tuacpi_char;
  end;
  {$if sizeof(Tacpi_facs) <> 64}
    {$error sizeof(Tacpi_facs) <> 64}
  {$endif}

  Pacpi_mcfg_allocation = ^Tacpi_mcfg_allocation;
  Tacpi_mcfg_allocation = packed record
    address: Tuacpi_u64;
    segment: Tuacpi_u16;
    start_bus: Tuacpi_u8;
    end_bus: Tuacpi_u8;
    rsvd: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_mcfg_allocation) <> 16}
    {$error sizeof(Tacpi_mcfg_allocation) <> 16}
  {$endif}

  Pacpi_mcfg = ^Tacpi_mcfg;
  Tacpi_mcfg = packed record
    hdr: Tacpi_sdt_hdr;
    rsvd: Tuacpi_u64;
    // start of Tacpi_mcfg_allocation array
    entries: record end;
  end;
  {$if sizeof(Tacpi_mcfg) <> 44}
    {$error sizeof(Tacpi_mcfg) <> 44}
  {$endif}

const
  // Tacpi_hpet->block_id
  ACPI_HPET_PCI_VENDOR_ID_SHIFT = 16;
  ACPI_HPET_LEGACY_REPLACEMENT_IRQ_ROUTING_CAPABLE = 1 shl 15;
  ACPI_HPET_COUNT_SIZE_CAP = 1 shl 13;
  ACPI_HPET_NUMBER_OF_COMPARATORS_SHIFT = 8;
  ACPI_HPET_NUMBER_OF_COMPARATORS_MASK = %11111;
  ACPI_HPET_HARDWARE_REV_ID_MASK = %11111111;

  // Tacpi_hpet->flags
  ACPI_HPET_PAGE_PROTECTION_MASK = %11;
  ACPI_HPET_PAGE_NO_PROTECTION = 0;
  ACPI_HPET_PAGE_4K_PROTECTED = 1;
  ACPI_HPET_PAGE_64K_PROTECTED = 2;

type
  Pacpi_hpet = ^Tacpi_hpet;
  Tacpi_hpet = packed record
    hdr: Tacpi_sdt_hdr;
    block_id: Tuacpi_u32;
    address: Tacpi_gas;
    number: Tuacpi_u8;
    min_clock_tick: Tuacpi_u16;
    flags: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_hpet) <> 56}
    {$error sizeof(Tacpi_hpet) <> 56}
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
  ACPI_PM2_CNT_PRESERVE_MASK = not Tuacpi_u64(ACPI_PM2_CNT_ARB_DIS_MASK);

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
  ACPI_SLP_STS_PRESERVE_MASK = not Tuacpi_u64(ACPI_SLP_STS_WAK_STS_MASK);

  ACPI_SLP_STS_CLEAR = 1;

type
  Pacpi_dsdt = ^Tacpi_dsdt;
  Tacpi_dsdt = packed record
    hdr: Tacpi_sdt_hdr;
    definition_block: record end;
  end;

  Pacpi_ssdt = ^Tacpi_ssdt;
  Tacpi_ssdt = packed record
    hdr: Tacpi_sdt_hdr;
    definition_block: record end;
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
  Pacpi_ecdt = ^Tacpi_ecdt;
  Tacpi_ecdt = packed record
    hdr: Tacpi_sdt_hdr;
    ec_control: Tacpi_gas;
    ec_data: Tacpi_gas;
    uid: Tuacpi_u32;
    gpe_bit: Tuacpi_u8;
    // start of Tuacpi_char array
    ec_id: record end;
  end;
  {$if sizeof(Tacpi_ecdt) <> 65}
    {$error sizeof(Tacpi_ecdt) <> 65}
  {$endif}

  // Tacpi_dbg2_device_info->port_type
  Tacpi_dbg2_type = (
    ACPI_DBG2_TYPE_SERIAL = $8000,
    ACPI_DBG2_TYPE_1394 = $8001,
    ACPI_DBG2_TYPE_USB = $8002,
    ACPI_DBG2_TYPE_NET = $8003
  );

  (*
   * Constants for:
   * - Tacpi_dbg2_device_info->port_subtype
   *   if Tacpi_dbg2_device_info->port_type == ACPI_DBG2_TYPE_SERIAL.
   * - Tacpi_spcr->interface_type (there is no type/subtype distinction in SPCR).
   *)
  Tacpi_dbg2_serial_subtype = (
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
   * Constants for Tacpi_dbg2_device_info->port_subtype
   * if Tacpi_dbg2_device_info->port_type == ACPI_DBG2_TYPE_1394.
   *)
  Tacpi_dbg2_1394_subtype = (
    ACPI_DBG2_SUBTYPE_1394_STANDARD = $0
  );

  (*
   * Constants for Tacpi_dbg2_device_info->port_subtype
   * if Tacpi_dbg2_device_info->port_type == ACPI_DBG2_TYPE_USB.
   *)
  Tacpi_dbg2_usb_subtype = (
    ACPI_DBG2_SUBTYPE_USB_XHCI_DEBUG = $0,
    ACPI_DBG2_SUBTYPE_USB_EHCI_DEBUG = $1
  );

  Pacpi_dbg2 = ^Tacpi_dbg2;
  Tacpi_dbg2 = packed record
    hdr: Tacpi_sdt_hdr;
    offset_dbg_device_info: Tuacpi_u32;
    number_dbg_device_info: Tuacpi_u32;
    (*
     *  Variable length fields below:
     *  At ->offset_dbg_device_info:
     *    struct Tacpi_dbg2_dbg_device_info dbg_devices[number_dbg_device_info];
     *)
  end;
  {$if sizeof(Tacpi_dbg2) <> 44}
    {$error sizeof(Tacpi_dbg2) <> 44}
  {$endif}

  Pacpi_dbg2_dbg_device_info = ^Tacpi_dbg2_dbg_device_info;
  Tacpi_dbg2_dbg_device_info = packed record
    revision: Tuacpi_u8;
    length: Tuacpi_u16;
    number_generic_address_registers: Tuacpi_u8;
    namespace_string_length: Tuacpi_u16;
    namespace_string_offset: Tuacpi_u16;
    oem_data_length: Tuacpi_u16;
    oem_data_offset: Tuacpi_u16;
    port_type: Tuacpi_u16;
    port_subtype: Tuacpi_u16;
    rsvd: Tuacpi_u16;
    base_address_register_offset: Tuacpi_u16;
    address_size_offset: Tuacpi_u16;
    (*
     * Variable length fields below:
     * At ->base_address_register_offset:
     *     struct Tacpi_gas base_address_register[number_generic_address_registers];
     * At ->address_size_offset
     *     u32 address_size[number_generic_address_registers];
     * At ->namespace_string_offset:
     *     char namespace_string[namespace_string_length];
     * At ->oem_data_offset:
     *     char oem_data[oem_data_length];
     *)
  end;
  {$if sizeof(Tacpi_dbg2_dbg_device_info) <> 22}
    {$error sizeof(Tacpi_dbg2_dbg_device_info) <> 22}
  {$endif}

const
  // Tacpi_scpr->interrupt_type
  ACPI_SPCR_INTERRUPT_TYPE_8259 = $1;
  ACPI_SPCR_INTERRUPT_TYPE_IOAPIC = $2;
  ACPI_SPCR_INTERRUPT_TYPE_IOSAPIC = $4;
  ACPI_SPCR_INTERRUPT_TYPE_GIC = $8;
  ACPI_SPCR_INTERRUPT_TYPE_PLIC_APLIC = $10;

  // Tacpi_spcr->pci_flags
  ACPI_SPCR_PCI_FLAGS_DO_NOT_DISABLE = $1;

type
  // Tacpi_spcr->terminal_type
  Tacpi_spcr_terminal_type = (
    ACPI_SPCR_TERMINAL_TYPE_VT100 = 0,
    ACPI_SPCR_TERMINAL_TYPE_EXTENDED_VT100 = 1,
    ACPI_SPCR_TERMINAL_TYPE_VT_UTF8 = 2,
    ACPI_SPCR_TERMINAL_TYPE_ANSI = 3
  );

  Pacpi_spcr = ^Tacpi_spcr;
  Tacpi_spcr = packed record
    hdr: Tacpi_sdt_hdr;
    interface_type: Tuacpi_u8;
    rsvd: array [0..2] of Tuacpi_u8;
    base_address: Tacpi_gas;
    interrupt_type: Tuacpi_u8;
    irq: Tuacpi_u8;
    gsi: Tuacpi_u32;
    configured_baud_rate: Tuacpi_u8;
    parity: Tuacpi_u8;
    stop_bits: Tuacpi_u8;
    flow_control: Tuacpi_u8;
    terminal_type: Tuacpi_u8;
    language: Tuacpi_u8;
    pci_device_id: Tuacpi_u16;
    pci_vendor_id: Tuacpi_u16;
    pci_bus_number: Tuacpi_u8;
    pci_device_number: Tuacpi_u8;
    pci_function_number: Tuacpi_u8;
    pci_flags: Tuacpi_u32;
    pci_segment: Tuacpi_u8;
    uart_clock_frequency: Tuacpi_u32;
    precise_baud_rate: Tuacpi_u32;
    namespace_string_length: Tuacpi_u16;
    namespace_string_offset: Tuacpi_u16;
    (*
     * At ->namespace_string_offset:
     *    char namespace_string[namespace_string_length];
     *)
  end;
  {$if sizeof(Tacpi_spcr) <> 88}
    {$error sizeof(Tacpi_spcr) <> 88}
  {$endif}

  Pacpi_rhct_hdr = ^Tacpi_rhct_hdr;
  Tacpi_rhct_hdr = packed record
    &type: Tuacpi_u16;
    length: Tuacpi_u16;
    revision: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_rhct_hdr) <> 6}
    {$error sizeof(Tacpi_rhct_hdr) <> 6}
  {$endif}

const
  // Tacpi_rhct->flags
  ACPI_TIMER_CANNOT_WAKE_CPU = 1 shl 0;

type
  Pacpi_rhct = ^Tacpi_rhct;
  Tacpi_rhct = packed record
    hdr: Tacpi_sdt_hdr;
    flags: Tuacpi_u32;
    timebase_frequency: Tuacpi_u64;
    node_count: Tuacpi_u32;
    nodes_offset: Tuacpi_u32;
    // start of Tacpi_rhct_hdr array
    entries: record end;
  end;
  {$if sizeof(Tacpi_rhct) <> 56}
    {$error sizeof(Tacpi_rhct) <> 56}
  {$endif}

  Tacpi_rhct_entry_type = (
    ACPI_RHCT_ENTRY_TYPE_ISA_STRING = 0,
    ACPI_RHCT_ENTRY_TYPE_CMO = 1,
    ACPI_RHCT_ENTRY_TYPE_MMU = 2,
    ACPI_RHCT_ENTRY_TYPE_HART_INFO = 65535
  );

  Pacpi_rhct_isa_string = ^Tacpi_rhct_isa_string;
  Tacpi_rhct_isa_string = packed record
    hdr: Tacpi_rhct_hdr;
    length: Tuacpi_u16;
    // start of Tuacpi_u8 array
    isa: record end;
  end;
  {$if sizeof(Tacpi_rhct_isa_string) <> 8}
    {$error sizeof(Tacpi_rhct_isa_string) <> 8}
  {$endif}

  Pacpi_rhct_cmo = ^Tacpi_rhct_cmo;
  Tacpi_rhct_cmo = packed record
    hdr: Tacpi_rhct_hdr;
    rsvd: Tuacpi_u8;
    cbom_size: Tuacpi_u8;
    cbop_size: Tuacpi_u8;
    cboz_size: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_rhct_cmo) <> 10}
    {$error sizeof(Tacpi_rhct_cmo) <> 10}
  {$endif}

  Tacpi_rhct_mmu_type = (
    ACPI_RHCT_MMU_TYPE_SV39 = 0,
    ACPI_RHCT_MMU_TYPE_SV48 = 1,
    ACPI_RHCT_MMU_TYPE_SV57 = 2
  );

  Pacpi_rhct_mmu = ^Tacpi_rhct_mmu;
  Tacpi_rhct_mmu = packed record
    hdr: Tacpi_rhct_hdr;
    rsvd: Tuacpi_u8;
    &type: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_rhct_mmu) <> 8}
    {$error sizeof(Tacpi_rhct_mmu) <> 8}
  {$endif}

  Pacpi_rhct_hart_info = ^Tacpi_rhct_hart_info;
  Tacpi_rhct_hart_info = packed record
    hdr: Tacpi_rhct_hdr;
    offset_count: Tuacpi_u16;
    uid: Tuacpi_u32;
    // start of Tuacpi_u32 array
    offsets: record end;
  end;
  {$if sizeof(Tacpi_rhct_hart_info) <> 12}
    {$error sizeof(Tacpi_rhct_hart_info) <> 12}
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
   * For decode API & human usable structures refer to Tuacpi/resources.h
   *)
  Tacpi_small_item = packed record
    type_and_length: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_small_item) <> 1}
    {$error sizeof(Tacpi_small_item) <> 1}
  {$endif}

  Tacpi_resource_irq = packed record
    common: Tacpi_small_item;
    irq_mask: Tuacpi_u16;
    flags: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_irq) <> 4}
    {$error sizeof(Tacpi_resource_irq) <> 4}
  {$endif}

  Tacpi_resource_dma = packed record
    common: Tacpi_small_item;
    channel_mask: Tuacpi_u8;
    flags: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_dma) <> 3}
    {$error sizeof(Tacpi_resource_dma) <> 3}
  {$endif}

  Tacpi_resource_start_dependent = packed record
    common: Tacpi_small_item;
    flags: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_start_dependent) <> 2}
    {$error sizeof(Tacpi_resource_start_dependent) <> 2}
  {$endif}

  Tacpi_resource_end_dependent = packed record
    common: Tacpi_small_item;
  end;
  {$if sizeof(Tacpi_resource_end_dependent) <> 1}
    {$error sizeof(Tacpi_resource_end_dependent) <> 1}
  {$endif}

  Tacpi_resource_io = packed record
    common: Tacpi_small_item;
    information: Tuacpi_u8;
    minimum: Tuacpi_u16;
    maximum: Tuacpi_u16;
    alignment: Tuacpi_u8;
    length: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_io) <> 8}
    {$error sizeof(Tacpi_resource_io) <> 8}
  {$endif}

  Tacpi_resource_fixed_io = packed record
    common: Tacpi_small_item;
    address: Tuacpi_u16;
    length: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_fixed_io) <> 4}
    {$error sizeof(Tacpi_resource_fixed_io) <> 4}
  {$endif}

  Tacpi_resource_fixed_dma = packed record
    common: Tacpi_small_item;
    request_line: Tuacpi_u16;
    channel: Tuacpi_u16;
    transfer_width: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_fixed_dma) <> 6}
    {$error sizeof(Tacpi_resource_fixed_dma) <> 6}
  {$endif}

  Tacpi_resource_vendor_defined_type0 = packed record
    common: Tacpi_small_item;
    // start of Tuacpi_u8 array
    byte_data: record end;
  end;
  {$if sizeof(Tacpi_resource_vendor_defined_type0) <> 1}
    {$error sizeof(Tacpi_resource_vendor_defined_type0) <> 1}
  {$endif}

  Tacpi_resource_end_tag = packed record
    common: Tacpi_small_item;
    checksum: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_end_tag) <> 2}
    {$error sizeof(Tacpi_resource_end_tag) <> 2}
  {$endif}

  Tacpi_large_item = packed record
    &type: Tuacpi_u8;
    length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_large_item) <> 3}
    {$error sizeof(Tacpi_large_item) <> 3}
  {$endif}

  Tacpi_resource_memory24 = packed record
    common: Tacpi_large_item;
    information: Tuacpi_u8;
    minimum: Tuacpi_u16;
    maximum: Tuacpi_u16;
    alignment: Tuacpi_u16;
    length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_memory24) <> 12}
    {$error sizeof(Tacpi_resource_memory24) <> 12}
  {$endif}

  Tacpi_resource_vendor_defined_type1 = packed record
    common: Tacpi_large_item;
    // start of Tuacpi_u8 array
    byte_data: record end;
  end;
  {$if sizeof(Tacpi_resource_vendor_defined_type1) <> 3}
    {$error sizeof(Tacpi_resource_vendor_defined_type1) <> 3}
  {$endif}

  Tacpi_resource_memory32 = packed record
    common: Tacpi_large_item;
    information: Tuacpi_u8;
    minimum: Tuacpi_u32;
    maximum: Tuacpi_u32;
    alignment: Tuacpi_u32;
    length: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_resource_memory32) <> 20}
    {$error sizeof(Tacpi_resource_memory32) <> 20}
  {$endif}

  Tacpi_resource_fixed_memory32 = packed record
    common: Tacpi_large_item;
    information: Tuacpi_u8;
    address: Tuacpi_u32;
    length: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_resource_fixed_memory32) <> 12}
    {$error sizeof(Tacpi_resource_fixed_memory32) <> 12}
  {$endif}

  Tacpi_resource_address = packed record
    common: Tacpi_large_item;
    &type: Tuacpi_u8;
    flags: Tuacpi_u8;
    type_flags: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_address) <> 6}
    {$error sizeof(Tacpi_resource_address) <> 6}
  {$endif}

  Tacpi_resource_address64 = packed record
    common: Tacpi_resource_address;
    granularity: Tuacpi_u64;
    minimum: Tuacpi_u64;
    maximum: Tuacpi_u64;
    translation_offset: Tuacpi_u64;
    length: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_resource_address64) <> 46}
    {$error sizeof(Tacpi_resource_address64) <> 46}
  {$endif}

  Tacpi_resource_address32 = packed record
    common: Tacpi_resource_address;
    granularity: Tuacpi_u32;
    minimum: Tuacpi_u32;
    maximum: Tuacpi_u32;
    translation_offset: Tuacpi_u32;
    length: Tuacpi_u32;
  end;
  {$if sizeof(Tacpi_resource_address32) <> 26}
    {$error sizeof(Tacpi_resource_address32) <> 26}
  {$endif}

  Tacpi_resource_address16 = packed record
    common: Tacpi_resource_address;
    granularity: Tuacpi_u16;
    minimum: Tuacpi_u16;
    maximum: Tuacpi_u16;
    translation_offset: Tuacpi_u16;
    length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_address16) <> 16}
    {$error sizeof(Tacpi_resource_address16) <> 16}
  {$endif}

  Tacpi_resource_address64_extended = packed record
    common: Tacpi_resource_address;
    revision_id: Tuacpi_u8;
    rsvd: Tuacpi_u8;
    granularity: Tuacpi_u64;
    minimum: Tuacpi_u64;
    maximum: Tuacpi_u64;
    translation_offset: Tuacpi_u64;
    length: Tuacpi_u64;
    attributes: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_resource_address64_extended) <> 56}
    {$error sizeof(Tacpi_resource_address64_extended) <> 56}
  {$endif}

  Tacpi_resource_extended_irq = packed record
    common: Tacpi_large_item;
    flags: Tuacpi_u8;
    num_irqs: Tuacpi_u8;
    // start of Tuacpi_u32 array
    irqs: record end;
  end;
  {$if sizeof(Tacpi_resource_extended_irq) <> 5}
    {$error sizeof(Tacpi_resource_extended_irq) <> 5}
  {$endif}

  Tacpi_resource_generic_register = packed record
    common: Tacpi_large_item;
    address_space_id: Tuacpi_u8;
    bit_width: Tuacpi_u8;
    bit_offset: Tuacpi_u8;
    access_size: Tuacpi_u8;
    address: Tuacpi_u64;
  end;
  {$if sizeof(Tacpi_resource_generic_register) <> 15}
    {$error sizeof(Tacpi_resource_generic_register) <> 15}
  {$endif}

  Tacpi_resource_gpio_connection = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    &type: Tuacpi_u8;
    general_flags: Tuacpi_u16;
    connection_flags: Tuacpi_u16;
    pull_configuration: Tuacpi_u8;
    drive_strength: Tuacpi_u16;
    debounce_timeout: Tuacpi_u16;
    pin_table_offset: Tuacpi_u16;
    source_index: Tuacpi_u8;
    source_offset: Tuacpi_u16;
    vendor_data_offset: Tuacpi_u16;
    vendor_data_length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_gpio_connection) <> 23}
    {$error sizeof(Tacpi_resource_gpio_connection) <> 23}
  {$endif}

const
  ACPI_SERIAL_TYPE_I2C = 1;
  ACPI_SERIAL_TYPE_SPI = 2;
  ACPI_SERIAL_TYPE_UART = 3;
  ACPI_SERIAL_TYPE_CSI2 = 4;
  ACPI_SERIAL_TYPE_MAX = ACPI_SERIAL_TYPE_CSI2;

type
  Tacpi_resource_serial = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    source_index: Tuacpi_u8;
    &type: Tuacpi_u8;
    flags: Tuacpi_u8;
    type_specific_flags: Tuacpi_u16;
    type_specific_revision_id: Tuacpi_u8;
    type_data_length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_serial) <> 12}
    {$error sizeof(Tacpi_resource_serial) <> 12}
  {$endif}

  Tacpi_resource_serial_i2c = packed record
    common: Tacpi_resource_serial;
    connection_speed: Tuacpi_u32;
    slave_address: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_serial_i2c) <> 18}
    {$error sizeof(Tacpi_resource_serial_i2c) <> 18}
  {$endif}

  Tacpi_resource_serial_spi = packed record
    common: Tacpi_resource_serial;
    connection_speed: Tuacpi_u32;
    data_bit_length: Tuacpi_u8;
    phase: Tuacpi_u8;
    polarity: Tuacpi_u8;
    device_selection: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_serial_spi) <> 21}
    {$error sizeof(Tacpi_resource_serial_spi) <> 21}
  {$endif}

  Tacpi_resource_serial_uart = packed record
    common: Tacpi_resource_serial;
    baud_rate: Tuacpi_u32;
    rx_fifo: Tuacpi_u16;
    tx_fifo: Tuacpi_u16;
    parity: Tuacpi_u8;
    lines_enabled: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_serial_uart) <> 22}
    {$error sizeof(Tacpi_resource_serial_uart) <> 22}
  {$endif}

  Tacpi_resource_serial_csi2 = packed record
    common: Tacpi_resource_serial;
  end;
  {$if sizeof(Tacpi_resource_serial_csi2) <> 12}
    {$error sizeof(Tacpi_resource_serial_csi2) <> 12}
  {$endif}

  Tacpi_resource_pin_function = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    flags: Tuacpi_u16;
    pull_configuration: Tuacpi_u8;
    function_number: Tuacpi_u16;
    pin_table_offset: Tuacpi_u16;
    source_index: Tuacpi_u8;
    source_offset: Tuacpi_u16;
    vendor_data_offset: Tuacpi_u16;
    vendor_data_length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_pin_function) <> 18}
    {$error sizeof(Tacpi_resource_pin_function) <> 18}
  {$endif}

  Tacpi_resource_pin_configuration = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    flags: Tuacpi_u16;
    &type: Tuacpi_u8;
    value: Tuacpi_u32;
    pin_table_offset: Tuacpi_u16;
    source_index: Tuacpi_u8;
    source_offset: Tuacpi_u16;
    vendor_data_offset: Tuacpi_u16;
    vendor_data_length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_pin_configuration) <> 20}
    {$error sizeof(Tacpi_resource_pin_configuration) <> 20}
  {$endif}

  Tacpi_resource_pin_group = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    flags: Tuacpi_u16;
    pin_table_offset: Tuacpi_u16;
    source_lable_offset: Tuacpi_u16;
    vendor_data_offset: Tuacpi_u16;
    vendor_data_length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_pin_group) <> 14}
    {$error sizeof(Tacpi_resource_pin_group) <> 14}
  {$endif}

  Tacpi_resource_pin_group_function = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    flags: Tuacpi_u16;
    &function: Tuacpi_u16;
    source_index: Tuacpi_u8;
    source_offset: Tuacpi_u16;
    source_lable_offset: Tuacpi_u16;
    vendor_data_offset: Tuacpi_u16;
    vendor_data_length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_pin_group_function) <> 17}
    {$error sizeof(Tacpi_resource_pin_group_function) <> 17}
  {$endif}

  Tacpi_resource_pin_group_configuration = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    flags: Tuacpi_u16;
    &type: Tuacpi_u8;
    value: Tuacpi_u32;
    source_index: Tuacpi_u8;
    source_offset: Tuacpi_u16;
    source_lable_offset: Tuacpi_u16;
    vendor_data_offset: Tuacpi_u16;
    vendor_data_length: Tuacpi_u16;
  end;
  {$if sizeof(Tacpi_resource_pin_group_configuration) <> 20}
    {$error sizeof(Tacpi_resource_pin_group_configuration) <> 20}
  {$endif}

  Tacpi_resource_clock_input = packed record
    common: Tacpi_large_item;
    revision_id: Tuacpi_u8;
    flags: Tuacpi_u16;
    divisor: Tuacpi_u16;
    numerator: Tuacpi_u32;
    source_index: Tuacpi_u8;
  end;
  {$if sizeof(Tacpi_resource_clock_input) <> 13}
    {$error sizeof(Tacpi_resource_clock_input) <> 13}
  {$endif}
