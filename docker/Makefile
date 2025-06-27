
DOCKER_IMAGE_NAME=ch55x_programmer_builder

all:
	@echo "Build targets: "
	@echo "docker-image           Build an image for building tools with Docker"
	@echo "build                  Build project assets from within Docker container"
	@echo "flash                  Flash the firmware using tools in Docker container"
	@echo "shell                  Run a shell using the above image with Docker"

docker-image:
	docker build -t ${DOCKER_IMAGE_NAME} -f Dockerfile .

COMMON = run \
		--rm \
		--mount type=bind,source="`pwd`/../src",target=/build \
		-w /build \

reset_controller.bin:
	docker ${COMMON} \
		-it ${DOCKER_IMAGE_NAME} \
		/usr/bin/bash -c "make"

build: reset_controller.bin

flash: reset_controller.bin
	docker ${COMMON} \
		--privileged -v /dev/bus/usb:/dev/bus/usb \
		-it ${DOCKER_IMAGE_NAME} \
		/usr/bin/bash -c "chprog reset_controller.bin"
		
shell:
	docker ${COMMON} \
		-it ${DOCKER_IMAGE_NAME} \
		/usr/bin/bash

