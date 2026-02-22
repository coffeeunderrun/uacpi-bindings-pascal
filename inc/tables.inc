type
  puacpi_table_identifiers = ^uacpi_table_identifiers;
  uacpi_table_identifiers = record
    signature: uacpi_object_name;

    // if oemid[0] == 0 this field is ignored
    oemid: array [0..5] of uacpi_char;

    // if oem_table_id[0] == 0 this field is ignored
    oem_table_id: array [0..7] of uacpi_char;
  end;

  puacpi_table = ^uacpi_table;
  uacpi_table = record case Integer of
    0: (
      // virt_addr, ptr, and hdr are just different ways to refer to the same pointer.
      case Integer of
        0: (virt_addr: uacpi_virt_addr);
        1: (hdr: pacpi_sdt_hdr);
    );
    1: (
      ptr: Pointer;
      // Index number used to identify this table internally
      index: uacpi_size;
    );
  end;

(*
 * Install a table from either a virtual or a physical address.
 * The table is simply stored in the internal table array, and not loaded by
 * the interpreter (see uacpi_table_load).
 *
 * The table is optionally returned via 'out_table'.
 *
 * Manual calls to uacpi_table_install are not subject to filtering via the
 * table installation callback (if any).
 *)
function uacpi_table_install(
    ptr: Pointer;
    out_table: puacpi_table
): uacpi_status; cdecl; external;

function uacpi_table_install_physical(
    addr: uacpi_phys_addr;
    out_table: puacpi_table
): uacpi_status; cdecl; external;

(*
 * Helpers for finding tables.
 *
 * for find_by_signature:
 *     'signature' is an array of 4 characters, a null terminator is not
 *     necessary and can be omitted (especially useful for non-C language
 *     bindings)
 *
 * 'out_table' is a pointer to a caller allocated uacpi_table structure that
 * receives the table pointer & its internal index in case the call was
 * successful.
 *
 * NOTE:
 * The returned table's reference count is incremented by 1, which keeps its
 * mapping alive forever unless uacpi_table_unref() is called for this table
 * later on. Calling uacpi_table_find_next_with_same_signature() on a table also
 * drops its reference count by 1, so if you want to keep it mapped you must
 * manually call uacpi_table_ref() beforehand.
 *)

function uacpi_table_find_by_signature(
  const signature: puacpi_char;
  out_table: puacpi_table
): uacpi_status; cdecl; external;

function uacpi_table_find_next_with_same_signature(
    in_out_table: puacpi_table
): uacpi_status; cdecl; external;

function uacpi_table_find(
    const id: puacpi_table_identifiers;
    out_table: puacpi_table
): uacpi_status; cdecl; external;

(*
 * Increment/decrement a table's reference count.
 * The table is unmapped when the reference count drops to 0.
 *)
function uacpi_table_ref(table: puacpi_table): uacpi_status; cdecl; external;
function uacpi_table_unref(table: puacpi_table): uacpi_status; cdecl; external;

(*
 * Returns the pointer to a sanitized internal version of FADT.
 *
 * The revision is guaranteed to be correct. All of the registers are converted
 * to GAS format. Fields that might contain garbage are cleared.
 *)
function uacpi_table_fadt(out_fadt: ppacpi_fadt): uacpi_status; cdecl; external;

type
  uacpi_table_installation_disposition = (
    // Allow the table to be installed as-is
    UACPI_TABLE_INSTALLATION_DISPOSITON_ALLOW = 0,

    (*
     * Deny the table from being installed completely. This is useful for
     * debugging various problems, e.g. AML loading bad SSDTs that cause the
     * system to hang or enter an undesired state.
     *)
    UACPI_TABLE_INSTALLATION_DISPOSITON_DENY,

    (*
     * Override the table being installed with the table at the virtual address
     * returned in 'out_override_address'.
     *)
    UACPI_TABLE_INSTALLATION_DISPOSITON_VIRTUAL_OVERRIDE,

    (*
     * Override the table being installed with the table at the physical address
     * returned in 'out_override_address'.
     *)
    UACPI_TABLE_INSTALLATION_DISPOSITON_PHYSICAL_OVERRIDE
  );

  uacpi_table_installation_handler = function (
    hdr: pacpi_sdt_hdr;
    out_override_address: puacpi_u64
  ): uacpi_table_installation_disposition; cdecl;

(*
 * Set a handler that is invoked for each table before it gets installed.
 *
 * Depending on the return value, the table is either allowed to be installed
 * as-is, denied, or overriden with a new one.
 *)
function uacpi_set_table_installation_handler(
    handler: uacpi_table_installation_handler
): uacpi_status; cdecl; external;

type
  uacpi_subtable_iteration_callback = function (
    handle: uacpi_handle;
    hdr: pacpi_entry_hdr
  ): uacpi_iteration_decision; cdecl;

(*
 * Iterate every subtable of a table such as MADT or SRAT.
 *
 * 'hdr' is the pointer to the main table, 'hdr_size' is the number of bytes in
 * the table before the beginning of the subtable records. 'cb' is the callback
 * invoked for each subtable with the 'user' context pointer passed for every
 * invocation.
 *
 * Example usage:
 *    uacpi_table tbl;
 *
 *    uacpi_table_find_by_signature(ACPI_MADT_SIGNATURE, &tbl);
 *    uacpi_for_each_subtable(
 *        tbl.hdr, sizeof(struct acpi_madt), parse_madt, NULL
 *    );
 *)
function uacpi_for_each_subtable(
  hdr: pacpi_sdt_hdr;
  hdr_size: uacpi_size;
  cb: uacpi_subtable_iteration_callback;
  user: Pointer
): uacpi_status; cdecl; external;
