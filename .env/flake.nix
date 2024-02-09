{
  description = "NixOS workstation configs and user setup by abelleisle";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
    nixpkgs-unstable.url = "github:nixos/nixpkgs/nixpkgs-unstable";

    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, nixpkgs-unstable, flake-utils } @ inputs:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in {
        devShells.default =
          pkgs.mkShell {
            buildInputs = with pkgs; [
              gcc-arm-embedded
              gdb
              cmake
              gnumake
              openocd
              qemu
              zig
              zls
            ];

            shellHook = ''
              echo "Lab node development shell"
              if [ -x "$(command -v zsh)" ]; then
                echo "ZSH is installed!"
                echo "Using ZSH for shell"
                zsh
                exit
              else
                echo "ZSH is not installed.. Using default nix shell"
              fi
            '';
          };
      }
    );
}
