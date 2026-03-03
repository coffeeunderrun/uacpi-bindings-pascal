{$ifndef UACPI_BAREBONES_MODE}

(*
 * Checks whether the device at 'node' matches any of the PNP ids provided in
 * 'list' (terminated by a UACPI_NULL). This is done by first attempting to
 * match the value returned from _HID and then the value(s) from _CID.
 *
 * Note that the presence of the device (_STA) is not verified here.
 *)
function uacpi_device_matches_pnp_id(
  node: Puacpi_namespace_node;
  const list: PPuacpi_char
): Tuacpi_bool; cdecl; external;

(*
 * Find all the devices in the namespace starting at 'parent' matching the
 * specified 'hids' (terminated by a UACPI_NULL) against any value from _HID or
 * _CID. Only devices reported as present via _STA are checked. Any matching
 * devices are then passed to the 'cb'.
 *)
function uacpi_find_devices_at(
  parent: Puacpi_namespace_node;
  const hids: PPuacpi_char;
  cb: Tuacpi_iteration_callback;
  user: Pointer
): Tuacpi_status; cdecl; external;

(*
 * Same as uacpi_find_devices_at, except this starts at the root and only
 * matches one hid.
 *)
function uacpi_find_devices(
    const hid: PPuacpi_char;
    cb: Tuacpi_iteration_callback;
    user: Pointer
): Tuacpi_status; cdecl; external;

type
  Tuacpi_interrupt_model = (
    UACPI_INTERRUPT_MODEL_PIC = 0,
    UACPI_INTERRUPT_MODEL_IOAPIC,
    UACPI_INTERRUPT_MODEL_IOSAPIC,
    UACPI_INTERRUPT_MODEL_PLATFORM_SPECIFIC,
    UACPI_INTERRUPT_MODEL_GIC,
    UACPI_INTERRUPT_MODEL_LPIC,
    UACPI_INTERRUPT_MODEL_RINTC
  );

function uacpi_set_interrupt_model(model: Tuacpi_interrupt_model): Tuacpi_status; cdecl; external;

type
  Puacpi_pci_routing_table_entry = ^Tuacpi_pci_routing_table_entry;
  Tuacpi_pci_routing_table_entry = record
    address: Tuacpi_u32;
    index: Tuacpi_u32;
    source: Puacpi_namespace_node;
    pin: Tuacpi_u8;
  end;

  Puacpi_pci_routing_table = ^Tuacpi_pci_routing_table;
  Tuacpi_pci_routing_table = record
    num_entries: Tuacpi_size;
    entries: record end;
  end;

procedure uacpi_free_pci_routing_table(table: Puacpi_pci_routing_table); cdecl; external;

function uacpi_get_pci_routing_table(
    parent: Puacpi_namespace_node; out out_table: Puacpi_pci_routing_table
): Tuacpi_status; cdecl; external;

type
  Puacpi_id_string = ^Tuacpi_id_string;
  Tuacpi_id_string = record
    // size of the string including the null byte
    size: Tuacpi_u32;
    value: Puacpi_char;
  end;

procedure uacpi_free_id_string(id: Puacpi_id_string); cdecl; external;

(*
 * Evaluate a device's _HID method and get its value.
 * The returned struture must be freed using uacpi_free_id_string.
 *)
function uacpi_eval_hid(node: Puacpi_namespace_node; out out_id: Puacpi_id_string): Tuacpi_status; cdecl; external;

type
  Puacpi_pnp_id_list = ^Tuacpi_pnp_id_list;
  Tuacpi_pnp_id_list = record
    // number of 'ids' in the list
    num_ids: Tuacpi_u32;

    // size of the 'ids' list including the string lengths
    size: Tuacpi_u32;

    // list of PNP ids
    // Tuacpi_id_string ids[];
    ids: record end;
  end;

procedure uacpi_free_pnp_id_list(list: Puacpi_pnp_id_list); cdecl; external;

(*
 * Evaluate a device's _CID method and get its value.
 * The returned structure must be freed using uacpi_free_pnp_id_list.
 *)
function uacpi_eval_cid(node: Puacpi_namespace_node; out out_list: Puacpi_pnp_id_list): Tuacpi_status; cdecl; external;

(*
 * Evaluate a device's _STA method and get its value.
 * If this method is not found, the value of 'flags' is set to all ones.
 *)
function uacpi_eval_sta(node: Puacpi_namespace_node; out flags: Tuacpi_u32): Tuacpi_status; cdecl; external;

(*
 * Evaluate a device's _ADR method and get its value.
 *)
function uacpi_eval_adr(node: Puacpi_namespace_node; out out_adr: Tuacpi_u64): Tuacpi_status; cdecl; external;

(*
 * Evaluate a device's _CLS method and get its value.
 * The format of returned string is BBSSPP where:
 *     BB => Base Class (e.g. 01 => Mass Storage)
 *     SS => Sub-Class (e.g. 06 => SATA)
 *     PP => Programming Interface (e.g. 01 => AHCI)
 * The returned struture must be freed using uacpi_free_id_string.
 *)
function uacpi_eval_cls(node: Puacpi_namespace_node; out out_id: Puacpi_id_string): Tuacpi_status; cdecl; external;

(*
 * Evaluate a device's _UID method and get its value.
 * The returned struture must be freed using uacpi_free_id_string.
 *)
function uacpi_eval_uid(node: Puacpi_namespace_node; out out_id: Puacpi_id_string): Tuacpi_status; cdecl; external;

const
  // uacpi_namespace_node_info->flags
  UACPI_NS_NODE_INFO_HAS_ADR = (1 shl 0);
  UACPI_NS_NODE_INFO_HAS_HID = (1 shl 1);
  UACPI_NS_NODE_INFO_HAS_UID = (1 shl 2);
  UACPI_NS_NODE_INFO_HAS_CID = (1 shl 3);
  UACPI_NS_NODE_INFO_HAS_CLS = (1 shl 4);
  UACPI_NS_NODE_INFO_HAS_SXD = (1 shl 5);
  UACPI_NS_NODE_INFO_HAS_SXW = (1 shl 6);

type
  Puacpi_namespace_node_info = ^Tuacpi_namespace_node_info;
  Tuacpi_namespace_node_info = record
    // Size of the entire structure
    size: Tuacpi_u32;

    // Object information
    obj_name: Tuacpi_object_name;
    obj_type: Tuacpi_object_type;
    num_params: Tuacpi_u8;

    // UACPI_NS_NODE_INFO_HAS_*
    flags: Tuacpi_u8;

    (*
     * A mapping of [S1..S4] to the shallowest D state supported by the device
     * in that S state.
     *)
    sxd: array[0..3] of Tuacpi_u8;

    (*
     * A mapping of [S0..S4] to the deepest D state supported by the device
     * in that S state to be able to wake itself.
     *)
    sxw: array[0..4] of Tuacpi_u8;

    adr: Tuacpi_u64;
    hid: Tuacpi_id_string;
    uid: Tuacpi_id_string;
    cls: Tuacpi_id_string;
    cid: Tuacpi_pnp_id_list;
  end;

procedure uacpi_free_namespace_node_info(info: Puacpi_namespace_node_info); cdecl; external;

(*
 * Retrieve information about a namespace node. This includes the attached
 * object's type, name, number of parameters (if it's a method), the result of
 * evaluating _ADR, _UID, _CLS, _HID, _CID, as well as _SxD and _SxW.
 *
 * The returned structure must be freed with uacpi_free_namespace_node_info.
 *)
function uacpi_get_namespace_node_info(
    node: Puacpi_namespace_node; out out_info: Puacpi_namespace_node_info): Tuacpi_status; cdecl; external;

{$endif UACPI_BAREBONES_MODE}
