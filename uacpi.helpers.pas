unit uacpi.helpers;

{$if FPC_FULLVERSION < 30000}
  {$fatal "FPC 3.0.0 or later is required."}
{$endif}

{$modeswitch advancedrecords}
{$modeswitch typehelpers}

interface

uses uacpi;

type
  Tuacpi_pnp_id_list_helper = record helper for Tuacpi_pnp_id_list
    function GetId(Index: Tuacpi_u32): Tuacpi_id_string;
  end;

implementation

function Tuacpi_pnp_id_list_helper.GetId(Index: Tuacpi_u32): Tuacpi_id_string;
begin
  if Index >= Self.num_ids then exit(default(Tuacpi_id_string));
  result := Puacpi_id_string(@Self.Ids)[Index];
end;

end.
