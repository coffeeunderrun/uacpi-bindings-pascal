{$I platform/types.inc}

type
{$if not defined(CPU64) and defined(UACPI_PHYS_ADDR_IS_32BITS)}
  uacpi_phys_addr = uacpi_u32;
  uacpi_io_addr   = uacpi_u32;
{$else}
  uacpi_phys_addr = uacpi_u64;
  uacpi_io_addr   = uacpi_u64;
{$endif}

  puacpi_char = ^uacpi_char;

  puacpi_phys_addr = ^uacpi_phys_addr;
  puacpi_io_addr   = ^uacpi_io_addr;
