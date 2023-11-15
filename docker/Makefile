all:
	@echo "Build targets: "
	@echo "build-docker		Build an image for building tools with Docker"
	@echo "build			Build project assets from within Docker container"
	@echo "run			    Run a shell using the above image with Docker"

build-docker:
	docker build -t ch55x_programmer-builder -f Dockerfile .

COMMON = run \
		--rm \
		--mount type=bind,source="`pwd`/../src",target=/build \
		-w /build \

reset_controller.bin:
	docker ${COMMON} \
		-it ch55x_programmer-builder \
		/usr/bin/bash -c "make"

build: reset_controller.bin

flash: reset_controller.bin
	docker ${COMMON} \
		--privileged -v /dev/bus/usb:/dev/bus/usb \
		-it ch55x_programmer-builder \
		/usr/bin/bash -c "chprog reset_controller.bin"
		
run:
	docker ${COMMON} \
		-it ch55x_programmer-builder \
		/usr/bin/bash

