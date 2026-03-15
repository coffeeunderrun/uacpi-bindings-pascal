{$ifndef UACPI_BAREBONES_MODE}

type
  Tuacpi_vendor_interface = (
    UACPI_VENDOR_INTERFACE_NONE = 0,
    UACPI_VENDOR_INTERFACE_WINDOWS_2000,
    UACPI_VENDOR_INTERFACE_WINDOWS_XP,
    UACPI_VENDOR_INTERFACE_WINDOWS_XP_SP1,
    UACPI_VENDOR_INTERFACE_WINDOWS_SERVER_2003,
    UACPI_VENDOR_INTERFACE_WINDOWS_XP_SP2,
    UACPI_VENDOR_INTERFACE_WINDOWS_SERVER_2003_SP1,
    UACPI_VENDOR_INTERFACE_WINDOWS_VISTA,
    UACPI_VENDOR_INTERFACE_WINDOWS_SERVER_2008,
    UACPI_VENDOR_INTERFACE_WINDOWS_VISTA_SP1,
    UACPI_VENDOR_INTERFACE_WINDOWS_VISTA_SP2,
    UACPI_VENDOR_INTERFACE_WINDOWS_7,
    UACPI_VENDOR_INTERFACE_WINDOWS_8,
    UACPI_VENDOR_INTERFACE_WINDOWS_8_1,
    UACPI_VENDOR_INTERFACE_WINDOWS_10,
    UACPI_VENDOR_INTERFACE_WINDOWS_10_RS1,
    UACPI_VENDOR_INTERFACE_WINDOWS_10_RS2,
    UACPI_VENDOR_INTERFACE_WINDOWS_10_RS3,
    UACPI_VENDOR_INTERFACE_WINDOWS_10_RS4,
    UACPI_VENDOR_INTERFACE_WINDOWS_10_RS5,
    UACPI_VENDOR_INTERFACE_WINDOWS_10_19H1,
    UACPI_VENDOR_INTERFACE_WINDOWS_10_20H1,
    UACPI_VENDOR_INTERFACE_WINDOWS_11,
    UACPI_VENDOR_INTERFACE_WINDOWS_11_22H2
  );

(*
 * Returns the "latest" AML-queried _OSI vendor interface.
 *
 * E.g. for the following AML code:
 *     _OSI("Windows 2021")
 *     _OSI("Windows 2000")
 *
 * This function will return UACPI_VENDOR_INTERFACE_WINDOWS_11, since this is
 * the latest version of the interface the code queried, even though the
 * "Windows 2000" query came after "Windows 2021".
 *)
function uacpi_latest_queried_vendor_interface: Tuacpi_vendor_interface; cdecl; external;

type
  Tuacpi_interface_kind = (
    UACPI_INTERFACE_KIND_VENDOR = Tuacpi_u8(1 shl 0),
    UACPI_INTERFACE_KIND_FEATURE = Tuacpi_u8(1 shl 1),
    UACPI_INTERFACE_KIND_ALL = (Tuacpi_u8(UACPI_INTERFACE_KIND_VENDOR) or Tuacpi_u8(UACPI_INTERFACE_KIND_FEATURE))
  );

(*
 * Install or uninstall an interface.
 *
 * The interface kind is used for matching during interface enumeration in
 * uacpi_bulk_configure_interfaces().
 *
 * After installing an interface, all _OSI queries report it as supported.
 *)
function uacpi_install_interface(
  const name: Puacpi_char; kind: Tuacpi_interface_kind
): Tuacpi_status; cdecl; external;
function uacpi_uninstall_interface(const name: Puacpi_char): Tuacpi_status; cdecl; external;

type
  Tuacpi_host_interface = (
    UACPI_HOST_INTERFACE_MODULE_DEVICE = 1,
    UACPI_HOST_INTERFACE_PROCESSOR_DEVICE,
    UACPI_HOST_INTERFACE_3_0_THERMAL_MODEL,
    UACPI_HOST_INTERFACE_3_0_SCP_EXTENSIONS,
    UACPI_HOST_INTERFACE_PROCESSOR_AGGREGATOR_DEVICE
  );

(*
 * Same as install/uninstall interface, but comes with an enum of known
 * interfaces defined by the ACPI specification. These are disabled by default
 * as they depend on the host kernel support.
 *)
function uacpi_enable_host_interface(&interface: Tuacpi_host_interface): Tuacpi_status; cdecl; external;
function uacpi_disable_host_interface(&interface: Tuacpi_host_interface): Tuacpi_status; cdecl; external;

type
  Tuacpi_interface_handler = function(const name: Tuacpi_char; supported: Tuacpi_bool): Tuacpi_bool; cdecl;

(*
 * Set a custom interface query (_OSI) handler.
 *
 * This callback will be invoked for each _OSI query with the value
 * passed in the _OSI, as well as whether the interface was detected as
 * supported. The callback is able to override the return value dynamically
 * or leave it untouched if desired (e.g. if it simply wants to log something or
 * do internal bookkeeping of some kind).
 *)
function uacpi_set_interface_query_handler(handler: Tuacpi_interface_handler): Tuacpi_status; cdecl; external;

type
  Tuacpi_interface_action = (
    UACPI_INTERFACE_ACTION_DISABLE = 0,
    UACPI_INTERFACE_ACTION_ENABLE
  );

(*
 * Bulk interface configuration, used to disable or enable all interfaces that
 * match 'kind'.
 *
 * This is generally only needed to work around buggy hardware, for example if
 * requested from the kernel command line.
 *
 * By default, all vendor strings (like "Windows 2000") are enabled, and all
 * host features (like "3.0 Thermal Model") are disabled.
 *)
function uacpi_bulk_configure_interfaces(
    action: Tuacpi_interface_action; kind: Tuacpi_interface_kind
): Tuacpi_status; cdecl; external;

{$endif UACPI_BAREBONES_MODE}
