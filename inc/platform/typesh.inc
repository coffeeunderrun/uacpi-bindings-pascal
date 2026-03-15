{$ifdef UACPI_OVERRIDE_TYPES}

{$I uacpi_types.inc}

{$else}

const
  UACPI_TRUE  = true;
  UACPI_FALSE = false;
  UACPI_NULL  = nil;

type
  Tuacpi_u8  = Byte;
  Tuacpi_u16 = Word;
  Tuacpi_u32 = DWord;
  Tuacpi_u64 = QWord;

  Tuacpi_i8  = ShortInt;
  Tuacpi_i16 = SmallInt;
  Tuacpi_i32 = LongInt;
  Tuacpi_i64 = Int64;

  Tuacpi_bool = Boolean;
  Tuacpi_char = Char;

  Tuacpi_uintptr   = PtrUInt;
  Tuacpi_virt_addr = Tuacpi_uintptr;

  Tuacpi_size = SizeUInt;

{$endif UACPI_OVERRIDE_TYPES}
