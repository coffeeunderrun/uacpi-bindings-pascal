function Tuacpi_pnp_id_list_helper.GetId(Index: Tuacpi_u32): Tuacpi_id_string;
begin
  if Index >= Self.num_ids then exit(default(Tuacpi_id_string));
  result := Puacpi_id_string(@Self.Ids)[Index];
end;
