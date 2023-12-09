#!/bin/bash

# Prompt the user for input
read -p "Install dependencies? [y/n]: " userInput
lowerCase=$(echo $userInput | tr '[:upper:]' '[:lower:]')

# Install deps depending on OS
if [ "$lowerCase" == "y" ]; then

	case "$(uname -sr)" in
		Darwin*)
			which -s brew
			if [[ $? != 0 ]] ; then
				# Install Homebrew
				echo "Installing Homebrew..."
				/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
			else
				echo "Updating Homebrew..."
				brew update
			fi

			brew install sfml
			installPath=$(brew info sfml | grep -E "^/.*")
			echo "sfml installed to path: $installPath"
			;;
		Linux*)
			sudo apt-get -y install cmake libsfml-dev
			;;
		*)
			echo 'Unknown OS, aborting install'
			;;
	esac

elif [ "$lowerCase" == "n" ]; then
	echo "n"
else echo "Wrong input format, not installing deps"

fi

mkdir -p build
cd build || exit

# Run CMake to generate the build files
cmake ..

# Build the project using Make (or other build tool specified by CMake)
make
