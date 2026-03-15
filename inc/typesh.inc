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
  PPuacpi_char = ^Puacpi_char;

{$I statush.inc}

type
{$if not defined(CPU64) and defined(UACPI_PHYS_ADDR_IS_32BITS)}
  Tuacpi_phys_addr = Tuacpi_u32;
  Tuacpi_io_addr   = Tuacpi_u32;
{$else}
  Tuacpi_phys_addr = Tuacpi_u64;
  Tuacpi_io_addr   = Tuacpi_u64;
{$endif}

  Puacpi_phys_addr = ^Tuacpi_phys_addr;
  Puacpi_io_addr   = ^Tuacpi_io_addr;

  Puacpi_handle = ^Tuacpi_handle;
  Tuacpi_handle = Pointer;

  Puacpi_object = ^Tuacpi_object;
  Tuacpi_object = record end;

  Puacpi_object_name = ^Tuacpi_object_name;
  Tuacpi_object_name = record case Integer of
    0: (text: array [0..3] of Tuacpi_char);
    1: (id: Tuacpi_u32);
  end;

  Tuacpi_iteration_decision = (
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

  Tuacpi_address_space = (
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

function uacpi_address_space_to_string(space: Tuacpi_address_space): Puacpi_char; cdecl; external;

{$ifndef UACPI_BAREBONES_MODE}

type
  Tuacpi_init_level = (
    // Reboot state, nothing is available
    UACPI_INIT_LEVEL_EARLY = 0,

    (*
     * State after a successfull call to uacpi_initialize. Table API and
     * other helpers that don't depend on the ACPI namespace may be used.
     *)
    UACPI_INIT_LEVEL_SUBSYSTEM_INITIALIZED = 1,

    (*
     * State after a successfull call to uacpi_namespace_load. Most API may be
     * used, namespace can be iterated, etc.
     *)
    UACPI_INIT_LEVEL_NAMESPACE_LOADED = 2,

    (*
     * The final initialization stage, this is entered after the call to
     * uacpi_namespace_initialize. All API is available to use.
     *)
    UACPI_INIT_LEVEL_NAMESPACE_INITIALIZED = 3
  );

  Puacpi_pci_address = ^Tuacpi_pci_address;
  Tuacpi_pci_address = record
    segment: Tuacpi_u16;
    bus: Tuacpi_u8;
    device: Tuacpi_u8;
    func: Tuacpi_u8;
  end;

  Puacpi_data_view = ^Tuacpi_data_view;
  Tuacpi_data_view = record
    union: record case Integer of
      0: (bytes: Puacpi_u8);
      1: (const_bytes: Puacpi_u8);
      2: (text: Puacpi_char);
      3: (const_text: Puacpi_char);
      4: (data: Pointer);
      5: (const_data: Pointer);
    end;

    length: Tuacpi_size;
  end;

  Tuacpi_object_type = (
    UACPI_OBJECT_UNINITIALIZED = 0,
    UACPI_OBJECT_INTEGER = 1,
    UACPI_OBJECT_STRING = 2,
    UACPI_OBJECT_BUFFER = 3,
    UACPI_OBJECT_PACKAGE = 4,
    UACPI_OBJECT_FIELD_UNIT = 5,
    UACPI_OBJECT_DEVICE = 6,
    UACPI_OBJECT_EVENT = 7,
    UACPI_OBJECT_METHOD = 8,
    UACPI_OBJECT_MUTEX = 9,
    UACPI_OBJECT_OPERATION_REGION = 10,
    UACPI_OBJECT_POWER_RESOURCE = 11,
    UACPI_OBJECT_PROCESSOR = 12,
    UACPI_OBJECT_THERMAL_ZONE = 13,
    UACPI_OBJECT_BUFFER_FIELD = 14,
    UACPI_OBJECT_DEBUG = 16,

    UACPI_OBJECT_REFERENCE = 20,
    UACPI_OBJECT_BUFFER_INDEX = 21
    // UACPI_OBJECT_MAX_TYPE_VALUE = UACPI_OBJECT_BUFFER_INDEX
  );

  // Type bits for API requiring a bit mask, e.g. uacpi_eval_typed
  Tuacpi_object_type_bits = (
    UACPI_OBJECT_INTEGER_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_INTEGER)),
    UACPI_OBJECT_STRING_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_STRING)),
    UACPI_OBJECT_BUFFER_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_BUFFER)),
    UACPI_OBJECT_PACKAGE_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_PACKAGE)),
    UACPI_OBJECT_FIELD_UNIT_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_FIELD_UNIT)),
    UACPI_OBJECT_DEVICE_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_DEVICE)),
    UACPI_OBJECT_EVENT_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_EVENT)),
    UACPI_OBJECT_METHOD_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_METHOD)),
    UACPI_OBJECT_MUTEX_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_MUTEX)),
    UACPI_OBJECT_OPERATION_REGION_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_OPERATION_REGION)),
    UACPI_OBJECT_POWER_RESOURCE_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_POWER_RESOURCE)),
    UACPI_OBJECT_PROCESSOR_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_PROCESSOR)),
    UACPI_OBJECT_THERMAL_ZONE_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_THERMAL_ZONE)),
    UACPI_OBJECT_BUFFER_FIELD_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_BUFFER_FIELD)),
    UACPI_OBJECT_DEBUG_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_DEBUG)),
    UACPI_OBJECT_REFERENCE_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_REFERENCE)),
    UACPI_OBJECT_BUFFER_INDEX_BIT = (1 shl Tuacpi_u32(UACPI_OBJECT_BUFFER_INDEX)),
    UACPI_OBJECT_ANY_BIT = $FFFFFFFF
  );

{$I namespaceh.inc}

procedure uacpi_object_ref(obj: Puacpi_object); cdecl; external;
procedure uacpi_object_unref(obj: Puacpi_object); cdecl; external;

function uacpi_object_get_type(obj: Puacpi_object): Tuacpi_object_type; cdecl; external;
function uacpi_object_get_type_bit(obj: Puacpi_object): Tuacpi_object_type_bits; cdecl; external;

(*
 * Returns UACPI_TRUE if the provided object's type matches this type.
 *)
function uacpi_object_is(obj: Puacpi_object; obj_type: Tuacpi_object_type): Tuacpi_bool; cdecl; external;

(*
 * Returns UACPI_TRUE if the provided object's type is one of the values
 * specified in the 'type_mask' of UACPI_OBJECT_*_BIT.
 *)
function uacpi_object_is_one_of(obj: Puacpi_object; type_mask: Tuacpi_object_type_bits): Tuacpi_bool; cdecl; external;

function uacpi_object_type_to_string(obj_type: Tuacpi_object_type): Puacpi_char; cdecl; external;

(*
 * Create an uninitialized object. The object can be further overwritten via
 * uacpi_object_assign_* to anything.
 *)
function uacpi_object_create_uninitialized: Puacpi_object; cdecl; external;

(*
 * Create an integer object with the value provided.
 *)
function uacpi_object_create_integer(value: Tuacpi_u64): Puacpi_object; cdecl; external;

type
  uacpi_overflow_behavior = (
    UACPI_OVERFLOW_ALLOW = 0,
    UACPI_OVERFLOW_TRUNCATE,
    UACPI_OVERFLOW_DISALLOW
  );

(*
 * Same as uacpi_object_create_integer, but introduces additional ways to
 * control what happens if the provided integer is larger than 32-bits, and the
 * AML code expects 32-bit integers.
 *
 * - UACPI_OVERFLOW_ALLOW -> do nothing, same as the vanilla helper
 * - UACPI_OVERFLOW_TRUNCATE -> truncate the integer to 32-bits if it happens to
 *                              be larger than allowed by the DSDT
 * - UACPI_OVERFLOW_DISALLOW -> fail object creation with
 *                              UACPI_STATUS_INVALID_ARGUMENT if the provided
 *                              value happens to be too large
 *)
function uacpi_object_create_integer_safe(
  value: Tuacpi_u64;
  overflow: uacpi_overflow_behavior;
  out out_obj: Tuacpi_object
): Tuacpi_status; cdecl; external;

function uacpi_object_assign_integer(obj: Puacpi_object; value: Tuacpi_u64): Tuacpi_status; cdecl; external;
function uacpi_object_get_integer(obj: Puacpi_object; out out_value: Tuacpi_u64): Tuacpi_status; cdecl; external;

(*
 * Create a string/buffer object. Takes in a constant view of the data.
 *
 * NOTE: The data is copied to a separately allocated buffer and is not taken
 *       ownership of.
 *)
function uacpi_object_create_string(data: Tuacpi_data_view): Puacpi_object; cdecl; external;
function uacpi_object_create_cstring(data: Puacpi_char): Puacpi_object; cdecl; external;
function uacpi_object_create_buffer(data: Tuacpi_data_view): Puacpi_object; cdecl; external;

(*
 * Returns a writable view of the data stored in the string or buffer type
 * object.
 *)
function uacpi_object_get_string_or_buffer(obj: Puacpi_object; out out_view: Tuacpi_data_view): Tuacpi_status; cdecl; external;
function uacpi_object_get_string(obj: Puacpi_object; out out_view: Tuacpi_data_view): Tuacpi_status; cdecl; external;
function uacpi_object_get_buffer(obj: Puacpi_object; out out_view: Tuacpi_data_view): Tuacpi_status; cdecl; external;

(*
 * Returns UACPI_TRUE if the provided string object is actually an AML namepath.
 *
 * This can only be the case for package elements. If a package element is
 * specified as a path to an object in AML, it's not resolved by the interpreter
 * right away as it might not have been defined at that point yet, and is
 * instead stored as a special string object to be resolved by client code
 * when needed.
 *
 * Example usage:
 *     uacpi_namespace_node *target_node = UACPI_NULL;
 *
 *     uacpi_object *obj = UACPI_NULL;
 *     uacpi_eval(scope, path, UACPI_NULL, &obj);
 *
 *     uacpi_object_array arr;
 *     uacpi_object_get_package(obj, &arr);
 *
 *     if (uacpi_object_is_aml_namepath(arr.objects[0])) {
 *         uacpi_object_resolve_as_aml_namepath(
 *             arr.objects[0], scope, &target_node
 *         );
 *     }
 *)
function uacpi_object_is_aml_namepath(obj: Puacpi_object): Tuacpi_bool; cdecl; external;

(*
 * Resolve an AML namepath contained in a string object.
 *
 * This is only applicable to objects that are package elements. See an
 * explanation of how this works in the comment above the declaration of
 * uacpi_object_is_aml_namepath.
 *
 * This is a shorthand for:
 *     Tuacpi_data_view view;
 *     uacpi_object_get_string(object, &view);
 *
 *     target_node = uacpi_namespace_node_resolve_from_aml_namepath(
 *         scope, view.text
 *     );
 *)
function uacpi_object_resolve_as_aml_namepath(
    obj: Puacpi_object;
    scope: Puacpi_namespace_node;
    out out_node: Puacpi_namespace_node
): Tuacpi_status; cdecl; external;

(*
 * Make the provided object a string/buffer.
 * Takes in a constant view of the data to be stored in the object.
 *
 * NOTE: The data is copied to a separately allocated buffer and is not taken
 *       ownership of.
 *)
function uacpi_object_assign_string(obj: Puacpi_object; data: Tuacpi_data_view): Tuacpi_status; cdecl; external;
function uacpi_object_assign_buffer(obj: Puacpi_object; data: Tuacpi_data_view): Tuacpi_status; cdecl; external;

type
  Puacpi_object_array = ^Tuacpi_object_array;
  Tuacpi_object_array = record
    objects: ^Puacpi_object;
    count: Tuacpi_size;
  end;

(*
 * Create a package object and store all of the objects in the array inside.
 * The array is allowed to be empty.
 *
 * NOTE: the reference count of each object is incremented before being stored
 *       in the object. Client code must remove all of the locally created
 *       references at its own discretion.
 *)
function uacpi_object_create_package(arr: Tuacpi_object_array): Puacpi_object; cdecl; external;

(*
 * Returns the list of objects stored in a package object.
 *
 * NOTE: the reference count of the objects stored inside is not incremented,
 *       which means destorying/overwriting the object also potentially destroys
 *       all of the objects stored inside unless the reference count is
 *       incremented by the client via uacpi_object_ref.
 *)
function uacpi_object_get_package(obj: Puacpi_object; out out_arr: Tuacpi_object_array): Tuacpi_status; cdecl; external;

(*
 * Make the provided object a package and store all of the objects in the array
 * inside. The array is allowed to be empty.
 *
 * NOTE: the reference count of each object is incremented before being stored
 *       in the object. Client code must remove all of the locally created
 *       references at its own discretion.
 *)
function uacpi_object_assign_package(obj: Puacpi_object; arr: Tuacpi_object_array): Tuacpi_status; cdecl; external;

(*
 * Create a reference object and make it point to 'child'.
 *
 * NOTE: child's reference count is incremented by one. Client code must remove
 *       all of the locally created references at its own discretion.
 *)
function uacpi_object_create_reference(child: Puacpi_object): Puacpi_object; cdecl; external;

(*
 * Make the provided object a reference and make it point to 'child'.
 *
 * NOTE: child's reference count is incremented by one. Client code must remove
 *       all of the locally created references at its own discretion.
 *)
function uacpi_object_assign_reference(obj: Puacpi_object; child: Puacpi_object): Tuacpi_status; cdecl; external;

(*
 * Retrieve the object pointed to by a reference object.
 *
 * NOTE: the reference count of the returned object is incremented by one and
 *       must be uacpi_object_unref'ed by the client when no longer needed.
 *)
function uacpi_object_get_dereferenced(obj: Puacpi_object; out out_obj: Puacpi_object): Tuacpi_status; cdecl; external;

type
  Puacpi_processor_info = ^Tuacpi_processor_info;
  Tuacpi_processor_info = record
    id: Tuacpi_u8;
    block_address: Tuacpi_u32;
    block_length: Tuacpi_u8;
  end;

(*
 * Returns the information about the provided processor object.
 *)
function uacpi_object_get_processor_info(obj: Puacpi_object; out out_info: Tuacpi_processor_info): Tuacpi_status; cdecl; external;

type
  Puacpi_power_resource_info = ^Tuacpi_power_resource_info;
  Tuacpi_power_resource_info = record
    system_level: Tuacpi_u8;
    resource_order: Tuacpi_u16;
  end;

(*
 * Returns the information about the provided power resource object.
 *)
function uacpi_object_get_power_resource_info(obj: Puacpi_object; out out_info: Tuacpi_power_resource_info): Tuacpi_status; cdecl; external;

type
  Tuacpi_region_op = (
    // data => uacpi_region_attach_data
    UACPI_REGION_OP_ATTACH = 0,
    // data => uacpi_region_detach_data
    UACPI_REGION_OP_DETACH,

    // data => uacpi_region_rw_data
    UACPI_REGION_OP_READ,
    UACPI_REGION_OP_WRITE,

    // data => uacpi_region_pcc_send_data
    UACPI_REGION_OP_PCC_SEND,

    // data => uacpi_region_gpio_rw_data
    UACPI_REGION_OP_GPIO_READ,
    UACPI_REGION_OP_GPIO_WRITE,

    // data => uacpi_region_ipmi_rw_data
    UACPI_REGION_OP_IPMI_COMMAND,

    // data => uacpi_region_ffixedhw_rw_data
    UACPI_REGION_OP_FFIXEDHW_COMMAND,

    // data => uacpi_region_prm_rw_data
    UACPI_REGION_OP_PRM_COMMAND,

    // data => uacpi_region_serial_rw_data
    UACPI_REGION_OP_SERIAL_READ,
    UACPI_REGION_OP_SERIAL_WRITE
  );

  Puacpi_generic_region_info = ^Tuacpi_generic_region_info;
  Tuacpi_generic_region_info = record
    base: Tuacpi_u64;
    length: Tuacpi_u64;
  end;

  Puacpi_pcc_region_info = ^Tuacpi_pcc_region_info;
  Tuacpi_pcc_region_info = record
    buffer: Tuacpi_data_view;
    subspace_id: Tuacpi_u8;
  end;

  Puacpi_gpio_region_info = ^Tuacpi_gpio_region_info;
  Tuacpi_gpio_region_info = record
     num_pins: Tuacpi_u64;
  end;

  Puacpi_region_attach_data = ^Tuacpi_region_attach_data;
  Tuacpi_region_attach_data = record
    handler_context: Pointer;
    region_node: Puacpi_namespace_node;
    union: record case Integer of
      0: (generic_info: Tuacpi_generic_region_info);
      1: (pcc_info: Tuacpi_pcc_region_info);
      2: (gpio_info: Tuacpi_gpio_region_info);
    end;
    out_region_context: Pointer;
  end;

  Puacpi_region_rw_data = ^Tuacpi_region_rw_data;
  Tuacpi_region_rw_data = record
    handler_context: Pointer;
    region_context: Pointer;
    union: record case Integer of
      0: (address: Tuacpi_phys_addr);
      1: (offset: Tuacpi_u64);
    end;
    value: Tuacpi_u64;
    byte_width: Tuacpi_u8;
  end;

  Puacpi_region_pcc_send_data = ^Tuacpi_region_pcc_send_data;
  Tuacpi_region_pcc_send_data = record
    handler_context: Pointer;
    region_context: Pointer;
    buffer: Tuacpi_data_view;
  end;

  Puacpi_region_gpio_rw_data = ^Tuacpi_region_gpio_rw_data;
  Tuacpi_region_gpio_rw_data = record
    handler_context: Pointer;
    region_context: Pointer;
    connection: Tuacpi_data_view;
    pin_offset: Tuacpi_u32;
    num_pins: Tuacpi_u32;
    value: Tuacpi_u64;
  end;

  Puacpi_region_ipmi_rw_data = ^Tuacpi_region_ipmi_rw_data;
  Tuacpi_region_ipmi_rw_data = record
    handler_context: Pointer;
    region_context: Pointer;
    in_out_message: Tuacpi_data_view;
    command: Tuacpi_u64;
  end;

  Puacpi_region_ffixedhw_rw_data = ^Tuacpi_region_ffixedhw_rw_data;
  Tuacpi_region_ffixedhw_rw_data = Tuacpi_region_ipmi_rw_data;

  Puacpi_region_prm_rw_data = ^Tuacpi_region_prm_rw_data;
  Tuacpi_region_prm_rw_data = record
    handler_context: Pointer;
    region_context: Pointer;
    in_out_message: Tuacpi_data_view;
  end;

  Tuacpi_access_attribute = (
    UACPI_ACCESS_ATTRIBUTE_QUICK = $02,
    UACPI_ACCESS_ATTRIBUTE_SEND_RECEIVE = $04,
    UACPI_ACCESS_ATTRIBUTE_BYTE = $06,
    UACPI_ACCESS_ATTRIBUTE_WORD = $08,
    UACPI_ACCESS_ATTRIBUTE_BLOCK = $0A,
    UACPI_ACCESS_ATTRIBUTE_BYTES = $0B,
    UACPI_ACCESS_ATTRIBUTE_PROCESS_CALL = $0C,
    UACPI_ACCESS_ATTRIBUTE_BLOCK_PROCESS_CALL = $0D,
    UACPI_ACCESS_ATTRIBUTE_RAW_BYTES = $0E,
    UACPI_ACCESS_ATTRIBUTE_RAW_PROCESS_BYTES = $0F
  );

  Puacpi_region_serial_rw_data = ^Tuacpi_region_serial_rw_data;
  Tuacpi_region_serial_rw_data = record
    handler_context: Pointer;
    region_context: Pointer;
    command: Tuacpi_u64;
    connection: Tuacpi_data_view;
    in_out_buffer: Tuacpi_data_view;
    access_attribute: Tuacpi_access_attribute;

    (*
     * Applicable if access_attribute is one of:
     * - UACPI_ACCESS_ATTRIBUTE_BYTES
     * - UACPI_ACCESS_ATTRIBUTE_RAW_BYTES
     * - UACPI_ACCESS_ATTRIBUTE_RAW_PROCESS_BYTES
     *)
    access_length: Tuacpi_u8;
  end;

  Puacpi_region_detach_data = ^Tuacpi_region_detach_data;
  Tuacpi_region_detach_data = record
    handler_context: Pointer;
    region_context: Pointer;
    region_node: Puacpi_namespace_node;
  end;

  Tuacpi_region_handler = function(op: Tuacpi_region_op; op_data: Tuacpi_handle): Tuacpi_status; cdecl;

  Tuacpi_notify_handler = function(context: Tuacpi_handle; node: Puacpi_namespace_node; value: Tuacpi_u64): Tuacpi_status; cdecl;

  Tuacpi_firmware_request_type = (
    UACPI_FIRMWARE_REQUEST_TYPE_BREAKPOINT,
    UACPI_FIRMWARE_REQUEST_TYPE_FATAL
  );

  Puacpi_firmware_request = ^Tuacpi_firmware_request;
  Tuacpi_firmware_request = record
    &type: Tuacpi_u8;
    case Integer of
      0: (
        // UACPI_FIRMWARE_REQUEST_BREAKPOINT
        breakpoint: record
          // The context of the method currently being executed
          ctx: Tuacpi_handle;
        end;
      );
      1: (
        // UACPI_FIRMWARE_REQUEST_FATAL
        fatal: record
          &type: Tuacpi_u8;
          code: Tuacpi_u32;
          arg: Tuacpi_u64;
        end;
      );
  end;

const
  UACPI_INTERRUPT_NOT_HANDLED = 0;
  UACPI_INTERRUPT_HANDLED = 1;

type
  Puacpi_interrupt_ret = ^Tuacpi_interrupt_ret;
  Tuacpi_interrupt_ret = Tuacpi_u32;

  Tuacpi_interrupt_handler = function(context: Tuacpi_handle): Tuacpi_interrupt_ret; cdecl;

{$endif UACPI_BAREBONES_MODE}
