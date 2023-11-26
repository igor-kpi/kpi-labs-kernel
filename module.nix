{ stdenv, kernel }:

stdenv.mkDerivation {
  name = "test-modules-${kernel.version}";
  src = ./.;

  nativeBuildInputs = kernel.moduleBuildDependencies;

  makeFlags = [
    "KDIR=${kernel.dev}/lib/modules/${kernel.modDirVersion}/build"
    "INSTALL_MOD_PATH=$(out)"
  ] ++ kernel.makeFlags;
}
