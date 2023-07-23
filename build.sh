# Running this script will start a docker container where dependencies will be installed, ChipControl will be built, and the ChipControl Unit Tests will be run.

sudo docker build -t chipcontrol .

sudo docker run -v $(pwd):/ChipControlDemo chipcontrol