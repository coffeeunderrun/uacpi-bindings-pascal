unit uacpi;

{$packrecords C}

interface

const
  UACPI_MAJOR = 3;
  UACPI_MINOR = 2;
  UACPI_PATCH = 0;

{$I platform/arch_helpers.inc}
{$I platform/types.inc}

type
  Puacpi_u8  = ^Tuacpi_u8;
  Puacpi_u16 = ^Tuacpi_u16;
  Puacpi_u32 = ^Tuacpi_u32;
  Puacpi_u64 = ^Tuacpi_u64;

  Puacpi_i8  = ^Tuacpi_i8;
  Puacpi_i16 = ^Tuacpi_i16;
  Puacpi_i32 = ^Tuacpi_i32;
  Puacpi_i64 = ^Tuacpi_i64;

  Puacpi_char = ^Tuacpi_char;

{$I status.inc}
{$I namespace.inc}
{$I types.inc}
{$I log.inc}

{$I context.inc}
{$I acpi.inc}
{$I tables.inc}

(*
 * Set up early access to the table subsystem. What this means is:
 * - uacpi_table_find() and similar API becomes usable before the call to
 *   uacpi_initialize().
 * - No kernel API besides logging and map/unmap will be invoked at this stage,
 *   allowing for heap and scheduling to still be fully offline.
 * - The provided 'temporary_buffer' will be used as a temporary storage for the
 *   internal metadata about the tables (list, reference count, addresses,
 *   sizes, etc).
 * - The 'temporary_buffer' is replaced with a normal heap buffer allocated via
 *   uacpi_kernel_alloc() after the call to uacpi_initialize() and can therefore
 *   be reclaimed by the kernel.
 *
 * The approximate overhead per table is 56 bytes, so a buffer of 4096 bytes
 * yields about 73 tables in terms of capacity. uACPI also has an internal
 * static buffer for tables, "UACPI_STATIC_TABLE_ARRAY_LEN", which is configured
 * as 16 descriptors in length by default.
 *
 * This function is used to initialize the barebones mode, see
 * UACPI_BAREBONES_MODE in config.h for more information.
 *)
function uacpi_setup_early_table_access(
  temporary_buffer: Pointer;
  buffer_size: Tuacpi_size
): Tuacpi_status; cdecl; external;

const
  (*
   * Bad table checksum should be considered a fatal error
   * (table load is fully aborted in this case)
   *)
  UACPI_FLAG_BAD_CSUM_FATAL = (Tuacpi_u64(1) shl 0);

  (*
   * Unexpected table signature should be considered a fatal error
   * (table load is fully aborted in this case)
   *)
  UACPI_FLAG_BAD_TBL_SIGNATURE_FATAL = (Tuacpi_u64(1) shl 1);

  (*
   * Force uACPI to use RSDT even for later revisions
   *)
  UACPI_FLAG_BAD_XSDT = (Tuacpi_u64(1) shl 2);

  (*
   * If this is set, ACPI mode is not entered during the call to
   * uacpi_initialize. The caller is expected to enter it later at their own
   * discretion by using uacpi_enter_acpi_mode().
   *)
  UACPI_FLAG_NO_ACPI_MODE = (Tuacpi_u64(1) shl 3);

  (*
   * Don't create the \_OSI method when building the namespace.
   * Only enable this if you're certain that having this method breaks your AML
   * blob, a more atomic/granular interface management is available via osi.h
   *)
  UACPI_FLAG_NO_OSI = (Tuacpi_u64(1) shl 4);

  (*
   * Validate table checksums at installation time instead of first use.
   * Note that this makes uACPI map the entire table at once, which not all
   * hosts are able to handle at early init.
   *)
  UACPI_FLAG_PROACTIVE_TBL_CSUM = (Tuacpi_u64(1) shl 5);

{$ifndef UACPI_BAREBONES_MODE}

(*
 * Initializes the uACPI subsystem, iterates & records all relevant RSDT/XSDT
 * tables. Enters ACPI mode.
 *
 * 'flags' is any combination of UACPI_FLAG_* above
 *)
function uacpi_initialize(flags: Tuacpi_u64): Tuacpi_status; cdecl; external;

(*
 * Parses & executes all of the DSDT/SSDT tables.
 * Initializes the event subsystem.
 *)
function uacpi_namespace_load: Tuacpi_status; cdecl; external;

(*
 * Initializes all the necessary objects in the namespaces by calling
 * _STA/_INI etc.
 *)
function uacpi_namespace_initialize: Tuacpi_status; cdecl; external;

// Returns the current subsystem initialization level
function uacpi_get_current_init_level: Tuacpi_init_level; cdecl; external;

(*
 * Evaluate an object within the namespace and get back its value.
 * Either root or path must be valid.
 * A value of NULL for 'parent' implies uacpi_namespace_root() relative
 * lookups, unless 'path' is already absolute.
 *)
function uacpi_eval(
  parent: Puacpi_namespace_node;
  const path: PChar;
  const args: Puacpi_object_array;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

function uacpi_eval_simple(
  parent: Puacpi_namespace_node;
  const path: PChar;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

(*
 * Same as uacpi_eval() but without a return value.
 *)
function uacpi_execute(
  parent: Puacpi_namespace_node;
  const path: PChar;
  args: Puacpi_object_array
): Tuacpi_status; cdecl; external;

function uacpi_execute_simple(
  parent: Puacpi_namespace_node;
  const path: PChar
): Tuacpi_status; cdecl; external;

(*
 * Same as uacpi_eval, but the return value type is validated against
 * the 'ret_mask'. UACPI_STATUS_TYPE_MISMATCH is returned on error.
 *)
function uacpi_eval_typed(
  parent: Puacpi_namespace_node;
  const path: PChar;
  const args: Puacpi_object_array;
  ret_mask: Tuacpi_object_type_bits;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

function uacpi_eval_simple_typed(
  parent: Puacpi_namespace_node;
  const path: PChar;
  ret_mask: Tuacpi_object_type_bits;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

(*
 * A shorthand for uacpi_eval_typed with UACPI_OBJECT_INTEGER_BIT.
 *)
function uacpi_eval_integer(
  parent: Puacpi_namespace_node;
  const path: PChar;
  const args: Puacpi_object_array;
  out out_value: Tuacpi_u64
): Tuacpi_status; cdecl; external;

function uacpi_eval_simple_integer(
  parent: Puacpi_namespace_node;
  const path: PChar;
  out out_value: Tuacpi_u64
): Tuacpi_status; cdecl; external;

(*
 * A shorthand for uacpi_eval_typed with
 *     UACPI_OBJECT_BUFFER_BIT | UACPI_OBJECT_STRING_BIT
 *
 * Use uacpi_object_get_string_or_buffer to retrieve the resulting buffer data.
 *)
function uacpi_eval_buffer_or_string(
  parent: Puacpi_namespace_node;
  const path: PChar;
  const args: Puacpi_object_array;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

function uacpi_eval_simple_buffer_or_string(
  parent: Puacpi_namespace_node;
  const path: PChar;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

(*
 * A shorthand for uacpi_eval_typed with UACPI_OBJECT_STRING_BIT.
 *
 * Use uacpi_object_get_string to retrieve the resulting buffer data.
 *)
function uacpi_eval_string(
  parent: Puacpi_namespace_node;
  const path: PChar;
  const args: Puacpi_object_array;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

function uacpi_eval_simple_string(
  parent: Puacpi_namespace_node;
  const path: PChar;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

(*
 * A shorthand for uacpi_eval_typed with UACPI_OBJECT_BUFFER_BIT.
 *
 * Use uacpi_object_get_buffer to retrieve the resulting buffer data.
 *)
function uacpi_eval_buffer(
  parent: Puacpi_namespace_node;
  const path: PChar;
  const args: Puacpi_object_array;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

function uacpi_eval_simple_buffer(
  parent: Puacpi_namespace_node;
  const path: PChar;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

(*
 * A shorthand for uacpi_eval_typed with UACPI_OBJECT_PACKAGE_BIT.
 *
 * Use uacpi_object_get_package to retrieve the resulting object array.
 *)
function uacpi_eval_package(
  parent: Puacpi_namespace_node;
  const path: PChar;
  const args: Puacpi_object_array;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

function uacpi_eval_simple_package(
  parent: Puacpi_namespace_node;
  const path: PChar;
  out ret: Puacpi_object
): Tuacpi_status; cdecl; external;

(*
 * Get the bitness of the currently loaded AML code according to the DSDT.
 *
 * Returns either 32 or 64.
 *)
function uacpi_get_aml_bitness(out out_bitness: Tuacpi_u8): Tuacpi_status; cdecl; external;

(*
 * Helpers for entering & leaving ACPI mode. Note that ACPI mode is entered
 * automatically during the call to uacpi_initialize().
 *)
{$ifdef UACPI_REDUCED_HARDWARE}
function uacpi_enter_acpi_mode: Tuacpi_status; cdecl;
function uacpi_leave_acpi_mode: Tuacpi_status; cdecl;
{$else UACPI_REDUCED_HARDWARE}
function uacpi_enter_acpi_mode: Tuacpi_status; cdecl; external;
function uacpi_leave_acpi_mode: Tuacpi_status; cdecl; external;
{$endif UACPI_REDUCED_HARDWARE}

(*
 * Attempt to acquire the global lock for 'timeout' milliseconds.
 * 0xFFFF implies infinite wait.
 *
 * On success, 'out_seq' is set to a unique sequence number for the current
 * acquire transaction. This number is used for validation during release.
 *)

function uacpi_acquire_global_lock(timeout: Tuacpi_u16; out out_seq: Tuacpi_u32): Tuacpi_status; cdecl; external;
function uacpi_release_global_lock(seq: Tuacpi_u32): Tuacpi_status; cdecl; external;


{$endif UACPI_BAREBONES_MODE}

(*
 * Reset the global uACPI state by freeing all internally allocated data
 * structures & resetting any global variables. After this call, uACPI must be
 * re-initialized from scratch to be used again.
 *
 * This is called by uACPI automatically if a fatal error occurs during a call
 * to uacpi_initialize/uacpi_namespace_load etc. in order to prevent accidental
 * use of partially uninitialized subsystems.
 *)
procedure uacpi_state_reset; cdecl; external;

implementation

{$ifdef UACPI_REDUCED_HARDWARE}
function uacpi_enter_acpi_mode: Tuacpi_status;
begin
  result := UACPI_STATUS_OK;
end;

function uacpi_leave_acpi_mode: Tuacpi_status;
begin
  result := UACPI_STATUS_COMPILED_OUT;
end;
{$endif UACPI_REDUCED_HARDWARE}

end.
