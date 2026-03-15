type
  Tuacpi_pnp_id_list_helper = record helper for Tuacpi_pnp_id_list
    function GetId(Index: Tuacpi_u32): Tuacpi_id_string;
  end;
