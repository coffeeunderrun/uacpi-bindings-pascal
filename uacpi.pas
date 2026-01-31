unit Uacpi;

interface

type
  PUacpiChar = ^UacpiChar;
  UacpiChar  = Char;

  UacpiI8  = ShortInt;
  UacpiI16 = SmallInt;
  UacpiI32 = LongInt;
  UacpiI64 = Int64;

  UacpiU8  = Byte;
  UacpiU16 = Word;
  UacpiU32 = DWord;
  UacpiU64 = QWord;

  UacpiSize     = SizeUInt;
  UacpiUIntPtr  = PtrUInt;
  UacpiIoAddr   = UacpiU64;

  PUacpiPhysAddr = ^UacpiPhysAddr;
  UacpiPhysAddr  = UacpiU64;

  UacpiLogLevel = (
    UACPI_LOG_DEBUG := 5,
    UACPI_LOG_TRACE := 4,
    UACPI_LOG_INFO := 3,
    UACPI_LOG_WARN := 2,
    UACPI_LOG_ERROR := 1
  );

  UacpiStatus = (
    UACPI_STATUS_OK := 0,
    UACPI_STATUS_MAPPING_FAILED := 1,
    UACPI_STATUS_OUT_OF_MEMORY := 2,
    UACPI_STATUS_BAD_CHECKSUM := 3,
    UACPI_STATUS_INVALID_SIGNATURE := 4,
    UACPI_STATUS_INVALID_TABLE_LENGTH := 5,
    UACPI_STATUS_NOT_FOUND := 6,
    UACPI_STATUS_INVALID_ARGUMENT := 7,
    UACPI_STATUS_UNIMPLEMENTED := 8,
    UACPI_STATUS_ALREADY_EXISTS := 9,
    UACPI_STATUS_INTERNAL_ERROR := 10,
    UACPI_STATUS_TYPE_MISMATCH := 11,
    UACPI_STATUS_INIT_LEVEL_MISMATCH := 12,
    UACPI_STATUS_NAMESPACE_NODE_DANGLING := 13,
    UACPI_STATUS_NO_HANDLER := 14,
    UACPI_STATUS_NO_RESOURCE_END_TAG := 15,
    UACPI_STATUS_COMPILED_OUT := 16,
    UACPI_STATUS_HARDWARE_TIMEOUT := 17,
    UACPI_STATUS_TIMEOUT := 18,
    UACPI_STATUS_OVERRIDDEN := 19,
    UACPI_STATUS_DENIED := 20,
    UACPI_STATUS_AML_UNDEFINED_REFERENCE := $0EFF0000,
    UACPI_STATUS_AML_INVALID_NAMESTRING := $0EFF0001,
    UACPI_STATUS_AML_OBJECT_ALREADY_EXISTS := $0EFF0002,
    UACPI_STATUS_AML_INVALID_OPCODE := $0EFF0003,
    UACPI_STATUS_AML_INCOMPATIBLE_OBJECT_TYPE := $0EFF0004,
    UACPI_STATUS_AML_BAD_ENCODING := $0EFF0005,
    UACPI_STATUS_AML_OUT_OF_BOUNDS_INDEX := $0EFF0006,
    UACPI_STATUS_AML_SYNC_LEVEL_TOO_HIGH := $0EFF0007,
    UACPI_STATUS_AML_INVALID_RESOURCE := $0EFF0008,
    UACPI_STATUS_AML_LOOP_TIMEOUT := $0EFF0009,
    UACPI_STATUS_AML_CALL_STACK_DEPTH_LIMIT := $0EFF000A
  );

function UacpiSetupEarlyTableAccess(Buffer: Pointer; Size: UacpiSize): UacpiStatus; cdecl; external name 'uacpi_setup_early_table_access';

implementation

function MemCmp(const Ptr1: Pointer; const Ptr2: Pointer; Count: UacpiSize): Integer; cdecl; public name 'memcmp';
begin
  result := 0;
end;

function MemCpy(Dest: Pointer; const Source: Pointer; Size: UacpiSize): Pointer; cdecl; public name 'memcpy';
begin
  result := nil;
end;

function MemMove(Dest: Pointer; const Source: Pointer; Size: UacpiSize): Pointer; cdecl; public name 'memmove';
begin
  result := nil;
end;

procedure MemSet(Dest: Pointer; Value: UacpiI32; Size: UacpiSize); cdecl; public name 'memset';
begin
end;

procedure KernelLog(LogLevel: UacpiLogLevel; const Message: PUacpiChar); cdecl; public name 'uacpi_kernel_log';
begin
end;

function KernelMap(Address: UacpiPhysAddr; Size: UacpiSize): Pointer; cdecl; public name 'uacpi_kernel_map';
begin
  result := nil;
end;

procedure KernelUnmap(Ptr: Pointer; Size: UacpiSize); cdecl; public name 'uacpi_kernel_unmap';
begin
end;

function KernelGetRsdp(AddressPtr: PUacpiPhysAddr): UacpiStatus; cdecl; public name 'uacpi_kernel_get_rsdp';
begin
  result := UACPI_STATUS_NOT_FOUND;
end;

end.
