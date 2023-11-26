{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = { nixpkgs, ... }: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system}; 
  in {
    inherit pkgs;

    packages.${system} = rec {
      default = pkgs.linuxPackages.callPackage ./module.nix {};
      kernel = pkgs.linuxPackages.kernel;
      kbuild = pkgs.runCommand "kbuild" {} "ln -sf ${kernel.dev}/lib/modules/${kernel.modDirVersion}/build $out";
    };
  };
}
