{
	description = "clockin devenv";

	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
	};

	outputs = { self, nixpkgs }: let
		system = "x86_64-linux";
		pkgs = import nixpkgs { inherit system; };

		lib = nixpkgs.lib;

		collapse_multiline = { separator, string }:
			let
				split_string = lib.strings.splitString "\n" string;
				trim_string = line: lib.strings.trimWith { start = true; end = true; } line;
				string_array = map (line: trim_string line) split_string;
				out = lib.strings.concatStringsSep separator string_array;
			in out;
	in {
		devShells.x86_64-linux.default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } {
			name = "clockin";

			buildInputs = with pkgs; [
				clang-tools
				gnumake

				curl

				concord
			];

			shellHook = let
				clangd_flags = collapse_multiline {
					string = ''
						-isystem${pkgs.clangStdenv.cc.libc.dev}/include/
						-isystem${pkgs.curl.dev}/include/
						-isystem${pkgs.concord}/include/
					'';
					separator = "\n";
				};
			in ''
				echo -e "${clangd_flags}" > compile_flags.txt
			'';
		};
	};
}
