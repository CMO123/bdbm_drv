/*
The MIT License (MIT)

Copyright (c) 2014-2015 CSAIL, MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

int main (int argc, char** argv)
{
	int32_t dev_h = -1;
	char* dev_name = "/dev/kernel_nvme/control";
	int i = 0;

	fprintf (stderr, "BlueDBM format tools (Ver 0.1)\n\n");

	/* Open the BDBM device */
	if ((dev_h = open (dev_name, O_RDWR)) == -1) {
		fprintf (stderr, "Failed to open '%s'\n", dev_name);
		exit (-1);
	}
	fprintf (stderr, "Open '%s' successfully\n", dev_name);

	/* Send a BDBM format command using IOCTL 
	 * Everything will be done by bdbm_drv.ko */
	for (i = 0; i < 500; i++) {
		ioctl (dev_h, 1, 0);
		ioctl (dev_h, 0, 0);
	}

	/* close the device */
	if (dev_h != -1) {
		close (dev_h);
	}

	return 0;
}

