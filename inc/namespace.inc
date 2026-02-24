{$ifndef UACPI_BAREBONES_MODE}

type
  Puacpi_namespace_node = ^Tuacpi_namespace_node;
  Tuacpi_namespace_node = record end;

function uacpi_namespace_root: Puacpi_namespace_node; cdecl; external;

type
  Tuacpi_predefined_namespace = (
    UACPI_PREDEFINED_NAMESPACE_ROOT = 0,
    UACPI_PREDEFINED_NAMESPACE_GPE,
    UACPI_PREDEFINED_NAMESPACE_PR,
    UACPI_PREDEFINED_NAMESPACE_SB,
    UACPI_PREDEFINED_NAMESPACE_SI,
    UACPI_PREDEFINED_NAMESPACE_TZ,
    UACPI_PREDEFINED_NAMESPACE_GL,
    UACPI_PREDEFINED_NAMESPACE_OS,
    UACPI_PREDEFINED_NAMESPACE_OSI,
    UACPI_PREDEFINED_NAMESPACE_REV,
    UACPI_PREDEFINED_NAMESPACE_MAX = UACPI_PREDEFINED_NAMESPACE_REV
  );

function uacpi_namespace_get_predefined(
    predefined: Tuacpi_predefined_namespace
): Puacpi_namespace_node; cdecl; external;

(*
 * Returns UACPI_TRUE if the provided 'node' is an alias.
 *)
function uacpi_namespace_node_is_alias(node: Puacpi_namespace_node): Tuacpi_bool; cdecl; external;

function uacpi_namespace_node_name(const node: Puacpi_namespace_node): Tuacpi_object_name; cdecl; external;

(*
 * Returns the type of object stored at the namespace node.
 *
 * NOTE: due to the existance of the CopyObject operator in AML, the
 *       return value of this function is subject to TOCTOU bugs.
 *)
function uacpi_namespace_node_type(
  const node: Puacpi_namespace_node; out out_type: Tuacpi_object_type
): Tuacpi_status; cdecl; external;

(*
 * Returns UACPI_TRUE via 'out' if the type of the object stored at the
 * namespace node matches the provided value, UACPI_FALSE otherwise.
 *
 * NOTE: due to the existance of the CopyObject operator in AML, the
 *       return value of this function is subject to TOCTOU bugs.
 *)
function uacpi_namespace_node_is(
  const node: Puacpi_namespace_node; &type: Tuacpi_object_type; out out_value: Tuacpi_bool
): Tuacpi_status; cdecl; external;

(*
 * Returns UACPI_TRUE via 'out' if the type of the object stored at the
 * namespace node matches any of the type bits in the provided value,
 * UACPI_FALSE otherwise.
 *
 * NOTE: due to the existance of the CopyObject operator in AML, the
 *       return value of this function is subject to TOCTOU bugs.
 *)
function uacpi_namespace_node_is_one_of(
  const node: Puacpi_namespace_node; type_mask: Tuacpi_object_type_bits; out out_value: Tuacpi_bool
): Tuacpi_status; cdecl; external;

function uacpi_namespace_node_depth(const node: Puacpi_namespace_node): Tuacpi_size; cdecl; external;

function uacpi_namespace_node_parent(
  node: Puacpi_namespace_node
): Puacpi_namespace_node; cdecl; external;

function uacpi_namespace_node_find(
  parent: Puacpi_namespace_node;
  const path: Puacpi_char;
  out out_node: Puacpi_namespace_node
): Tuacpi_status; cdecl; external;

(*
 * Same as uacpi_namespace_node_find, except the search recurses upwards when
 * the namepath consists of only a single nameseg. Usually, this behavior is
 * only desired if resolving a namepath specified in an aml-provided object,
 * such as a package element.
 *)
function uacpi_namespace_node_resolve_from_aml_namepath(
  scope: Puacpi_namespace_node;
  const path: Puacpi_char;
  out out_node: Puacpi_namespace_node
): Tuacpi_status; cdecl; external;

type
  Tuacpi_iteration_callback = function(
    user: Pointer; node: Puacpi_namespace_node; node_depth: Tuacpi_u32
  ): Tuacpi_iteration_decision; cdecl;

const
  UACPI_MAX_DEPTH_ANY = $FFFFFFFF;

(*
 * Depth-first iterate the namespace starting at the first child of 'parent'.
 *)
function uacpi_namespace_for_each_child_simple(
  parent: Puacpi_namespace_node; callback: Tuacpi_iteration_callback; user: Pointer
): Tuacpi_status; cdecl; external;

(*
 * Depth-first iterate the namespace starting at the first child of 'parent'.
 *
 * 'descending_callback' is invoked the first time a node is visited when
 * walking down. 'ascending_callback' is invoked the second time a node is
 * visited after we reach the leaf node without children and start walking up.
 * Either of the callbacks may be NULL, but not both at the same time.
 *
 * Only nodes matching 'type_mask' are passed to the callbacks.
 *
 * 'max_depth' is used to limit the maximum reachable depth from 'parent',
 * where 1 is only direct children of 'parent', 2 is children of first-level
 * children etc. Use UACPI_MAX_DEPTH_ANY or -1 to specify infinite depth.
 *)
function uacpi_namespace_for_each_child(
  parent: Puacpi_namespace_node; descending_callback: Tuacpi_iteration_callback;
  ascending_callback: Tuacpi_iteration_callback;
  type_mask: Tuacpi_object_type_bits; max_depth: Tuacpi_u32; user: Pointer
): Tuacpi_status; cdecl; external;

(*
 * Retrieve the next peer namespace node of '*iter', or, if '*iter' is
 * UACPI_NULL, retrieve the first child of 'parent' instead. The resulting
 * namespace node is stored at '*iter'.
 *
 * This API can be used to implement an "iterator" version of the
 * for_each_child helpers.
 *
 * Example usage:
 *     void recurse(uacpi_namespace_node *parent) {
 *        uacpi_namespace_node *iter = UACPI_NULL;
 *
 *        while (uacpi_namespace_node_next(parent, &iter) == UACPI_STATUS_OK) {
 *             // Do something with iter...
 *             descending_callback(iter);
 *
 *             // Recurse down to walk over the children of iter
 *             recurse(iter);
 *        }
 *     }
 *
 * Prefer the for_each_child family of helpers if possible instead of this API
 * as they avoid recursion and/or the need to use dynamic data structures
 * entirely.
 *)
function uacpi_namespace_node_next(
  parent: Puacpi_namespace_node; out iter: Puacpi_namespace_node
): Tuacpi_status; cdecl; external;

(*
 * Retrieve the next peer namespace node of '*iter', or, if '*iter' is
 * UACPI_NULL, retrieve the first child of 'parent' instead. The resulting
 * namespace node is stored at '*iter'. Only nodes which type matches one
 * of the types set in 'type_mask' are returned.
 *
 * See comment above 'uacpi_namespace_node_next' for usage examples.
 *
 * Prefer the for_each_child family of helpers if possible instead of this API
 * as they avoid recursion and/or the need to use dynamic data structures
 * entirely.
 *)
function uacpi_namespace_node_next_typed(
  parent: Puacpi_namespace_node; out iter: Puacpi_namespace_node;
  type_mask: Tuacpi_object_type_bits
): Tuacpi_status; cdecl; external;

function uacpi_namespace_node_generate_absolute_path(
    const node: Puacpi_namespace_node
): Puacpi_char; cdecl; external;
procedure uacpi_free_absolute_path(const path: Puacpi_char); cdecl; external;

{$endif UACPI_BAREBONES_MODE}
