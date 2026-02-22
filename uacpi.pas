unit uacpi;

{$packrecords C}

interface

const
  UACPI_MAJOR = 3;
  UACPI_MINOR = 2;
  UACPI_PATCH = 0;

{$I types.inc}
{$I status.inc}
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
  buffer_size: uacpi_size
): uacpi_status; cdecl; external;

const
  (*
   * Bad table checksum should be considered a fatal error
   * (table load is fully aborted in this case)
   *)
  UACPI_FLAG_BAD_CSUM_FATAL = (QWord(1) shl 0);

  (*
   * Unexpected table signature should be considered a fatal error
   * (table load is fully aborted in this case)
   *)
  UACPI_FLAG_BAD_TBL_SIGNATURE_FATAL = (QWord(1) shl 1);

  (*
   * Force uACPI to use RSDT even for later revisions
   *)
  UACPI_FLAG_BAD_XSDT = (QWord(1) shl 2);

  (*
   * If this is set, ACPI mode is not entered during the call to
   * uacpi_initialize. The caller is expected to enter it later at their own
   * discretion by using uacpi_enter_acpi_mode().
   *)
  UACPI_FLAG_NO_ACPI_MODE = (QWord(1) shl 3);

  (*
   * Don't create the \_OSI method when building the namespace.
   * Only enable this if you're certain that having this method breaks your AML
   * blob, a more atomic/granular interface management is available via osi.h
   *)
  UACPI_FLAG_NO_OSI = (QWord(1) shl 4);

  (*
   * Validate table checksums at installation time instead of first use.
   * Note that this makes uACPI map the entire table at once, which not all
   * hosts are able to handle at early init.
   *)
  UACPI_FLAG_PROACTIVE_TBL_CSUM = (QWord(1) shl 5);

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

end.
