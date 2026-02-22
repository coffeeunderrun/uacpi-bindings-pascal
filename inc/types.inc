{$I platform/types.inc}

type
{$if not defined(CPU64) and defined(UACPI_PHYS_ADDR_IS_32BITS)}
  uacpi_phys_addr = uacpi_u32;
  uacpi_io_addr   = uacpi_u32;
{$else}
  uacpi_phys_addr = uacpi_u64;
  uacpi_io_addr   = uacpi_u64;
{$endif}

  puacpi_u8  = ^uacpi_u8;
  puacpi_u16 = ^uacpi_u16;
  puacpi_u32 = ^uacpi_u32;
  puacpi_u64 = ^uacpi_u64;

  puacpi_i8  = ^uacpi_i8;
  puacpi_i16 = ^uacpi_i16;
  puacpi_i32 = ^uacpi_i32;
  puacpi_i64 = ^uacpi_i64;

  puacpi_char = ^uacpi_char;

  puacpi_phys_addr = ^uacpi_phys_addr;
  puacpi_io_addr   = ^uacpi_io_addr;

  uacpi_handle = Pointer;

  uacpi_object_name = record
    text: array [0..3] of uacpi_char;
    id: uacpi_u32;
  end;

  uacpi_iteration_decision = (
    UACPI_ITERATION_DECISION_CONTINUE = 0,
    UACPI_ITERATION_DECISION_BREAK,

    (*
     * Ignore all of the children of the current node and proceed directly to
     * its peer nodes.
     *
     * Only applicable for API that interacts with the AML namespace such as
     * uacpi_namespace_for_each_child, uacpi_find_deivces, etc.
     *)
    UACPI_ITERATION_DECISION_NEXT_PEER
  );

  uacpi_address_space = (
    UACPI_ADDRESS_SPACE_SYSTEM_MEMORY = 0,
    UACPI_ADDRESS_SPACE_SYSTEM_IO = 1,
    UACPI_ADDRESS_SPACE_PCI_CONFIG = 2,
    UACPI_ADDRESS_SPACE_EMBEDDED_CONTROLLER = 3,
    UACPI_ADDRESS_SPACE_SMBUS = 4,
    UACPI_ADDRESS_SPACE_SYSTEM_CMOS = 5,
    UACPI_ADDRESS_SPACE_PCI_BAR_TARGET = 6,
    UACPI_ADDRESS_SPACE_IPMI = 7,
    UACPI_ADDRESS_SPACE_GENERAL_PURPOSE_IO = 8,
    UACPI_ADDRESS_SPACE_GENERIC_SERIAL_BUS = 9,
    UACPI_ADDRESS_SPACE_PCC = $0A,
    UACPI_ADDRESS_SPACE_PRM = $0B,
    UACPI_ADDRESS_SPACE_FFIXEDHW = $7F,

    // Internal type
    UACPI_ADDRESS_SPACE_TABLE_DATA = $DA1A
);

function uacpi_address_space_to_string(space: uacpi_address_space): puacpi_char; cdecl; external;
