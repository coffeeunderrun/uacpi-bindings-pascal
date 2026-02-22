{$ifdef UACPI_OVERRIDE_TYPES}

{$I uacpi_types.inc}

{$else}

const
  UACPI_TRUE  = true;
  UACPI_FALSE = false;
  UACPI_NULL  = nil;

type
  uacpi_u8  = Byte;
  uacpi_u16 = Word;
  uacpi_u32 = DWord;
  uacpi_u64 = QWord;

  uacpi_i8  = ShortInt;
  uacpi_i16 = SmallInt;
  uacpi_i32 = LongInt;
  uacpi_i64 = Int64;

  uacpi_bool = Boolean;
  uacpi_char = Char;

  uacpi_uintptr   = PtrUInt;
  uacpi_virt_addr = uacpi_uintptr;

  uacpi_size = SizeUInt;

{$endif UACPI_OVERRIDE_TYPES}
