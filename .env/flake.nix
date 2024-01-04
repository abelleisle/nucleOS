{
  description = "NucleOS Operating System";

  inputs =
    {
      nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
      flake-utils.url = "github:numtide/flake-utils";
    };

  outputs = inputs:
    let
      inherit (inputs) nixpkgs flake-utils;
    in
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in rec
        {
          devShells.default = pkgs.mkShell {
            nativeBuildInputs = with pkgs; [
              zig
              zls
            ];
            shellHook = ''
              $SHELL
              exit
            '';
          };
        }
      );
}
