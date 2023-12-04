.. _template:

Template
########

The sample demonstrates a template for the Sidewalk End Node application.
It supports BLE, LoRa and FSK link modes.

.. _template_requirements:

Requirements
************

The sample supports the following development kits:

+--------------------+----------+------------------------+------------------------------+
| Hardware platforms | PCA      | Board name             | Build target                 |
+====================+==========+========================+==============================+
| nRF52840 DK        | PCA10056 | `nrf52840dk_nrf52840`_ | ``nrf52840dk_nrf52840``      |
+--------------------+----------+------------------------+------------------------------+
| nRF5340 DK         | PCA10095 | `nrf5340dk_nrf5340`_   | ``nrf5340dk_nrf5340_cpuapp`` |
+--------------------+----------+------------------------+------------------------------+

Besides the development kit, a LoRa radio module is also needed for this sample if you build it with the LoRa or FSK configuration.
The supported modules are as follows:

+------------+---------------+------------+
| Radio chip | Board name    | Interface  |
+============+===============+============+
| `SX1262`_  | SX126xMB2xAS  | SPI @ 8Mhz |
+------------+---------------+------------+

.. note::
   The LoRa radio module shield must be connected to the development kit header, and the antenna has to be connected to the radio module.
   For the exact pin assignment, refer to the :ref:`setting_up_hardware_semtech_pinout` section.

.. _template_overview:

Overview
********

You can use this sample as a starting point to implement a Sidewalk device.
The sample shows implementation of the Sidewalk API.

.. _template_ui:

User interface
**************

A button action is triggered when you release the button.
To use a long press action, hold a button for 2 seconds or longer, and release it.

The button assignment is as follows:

   * Button 1 (long press):
      Factory reset - The application informs the Sidewalk stack about the factory reset event.
      The Sidewalk library clears its configuration from the non-volatile storage and also saved initial link type.
      After a successful sample restart, the device needs to be registered with the cloud services again.

   * Button 2:
      Change link type. There is a Circular link type change BLE -> FSK -> LoRa -> BLE ->. Selected link type is saved and set after sample restart. ``Button 1 (long press)`` reset link type to initial one defined by ``CONFIG_SIDEWALK_APP_LINK_TYPE_(BLE/LORA/FSK)``

   * Button 3:
      Send Hello - This action will queue a message to the cloud.
      If Sidewalk is not ready, it will simply show an error without sending the message.
      The queue will be processed eventually, and all the queued messages will be sent.
      In BLE the connection request will be set automatically if necessary.

   * Button 4 (long press):
      Enter DFU state - This action disables the Sidewalk stack and starts the Bluetooth LE SMP Server.
      You can update the firmware image using nRF Connect for mobile application.
      To exit DFU state, perform a power cycle on your device.

LEDs represent the current state of the application:

   * LED 1:
      Application ``Connected`` successfully.

   * LED 2:
      Application ``Registered`` successfully.

   * LED 3:
      Application ``time sync`` is successful.

   * LED 4:
      Application ``link`` is up.

Other states are routed to generic GPIO pins.
When the voltage drops to 0, entering low logic state, it means that one of the following states is active:

.. tabs::

   .. tab:: nRF52840

      * P1.1:
         ``DFU`` state.

      * P1.2:
         ``ERROR`` has occured.

      * P1.3:
         ``Sending`` pin is active when the packet is being transmitted.

      * P1.4:
         The ``Received`` pin is toggled ``on`` and immediately ``off`` when the packet has been received.

   .. tab:: nRF5340

      * P1.2:
         ``DFU`` state.

      * P1.3:
         The ``Received`` pin is toggled ``on`` and immediately ``off`` when the packet has been received.

      * P1.4:
         ``Sending`` pin is active when the packet is being transmitted.

      * P1.8:
         ``ERROR`` has occured.

.. _template_applications:

Application extensions
**********************

Power measurement application
=============================

The application may perform the common Sidewalk application steps such us:

#. Registration
#. Time sync
#. Send hello message to cloud
#. Echo messages received from cloud

This application is especially useful in ``release`` configuration to check power consumption in different Sidewalk states. The states can be monitor by GPIO.

CONFIG_SIDEWALK_APP_ECHO

You can specify the default transport protocol using Kconfig

CONFIG_SIDEWALK_APP_ECHO_LINK_BLE
Registers and operates in BLE.

CONFIG_SIDEWALK_APP_ECHO_LINK_FSK
Registers and operates in FSK.

CONFIG_SIDEWALK_APP_ECHO_LINK_LORA
Registers in BLE, then automatically switches and operates in LoRa.
If device is already registered start in LoRa after power up.

Sensor Demo application
=======================
See sensor_monitor sample

Empty application
=================
Application does not initialize Sidewalk. Together with CLI it will replace sid_dut.


.. _template_config:

Configuration
*************

When running the sample, you can use different configurations files depending on the supported features.

.. _template_build_type:

Build types
===========

Configuration files are provided for different build types and are located in the application root directory.

The :file:`prj.conf` file represents a ``debug`` build type.
Other build types are covered by dedicated files with the respective build type added to the file name.
For example, the ``release`` build type file is named :file:`prj_release.conf`.
The same naming convention is followed if a board has other configuration files that are, for example, associated with the partition layout or child image configuration.

Before you start testing the application, you can select one of the build types supported by the sample.
Depending on the selected board, a sample supports the following build types:

* ``debug`` -- Debug version of the application - can be used to enable additional features, such as logs or command-line shell, to verify the application behavior.
* ``release`` -- Release version of the application - can be used to enable only the necessary application functionalities to optimize its performance.
* ``no_dfu`` -- No DFU version of the application - Bootloader and DFU service will not be build. The rest is the same as in debug version.

You can build the ``release`` firmware for ``build_target`` by running the following command in the project directory:

.. parsed-literal::
   :class: highlight

   $ west build -b *build_target* -- -DCONF_FILE=prj_release.conf

For example:

.. code-block:: console

   $ west build -b nrf52840dk_nrf52840 -- -DCONF_FILE=prj_release.conf

.. note::
    Selecting a build type is optional.
    However, if the build type is not selected, the ``debug`` build type is used by default.

Command Line Interface
======================

The Sidewalk CLI can be set by the Kconfig

CONFIG_SIDEWALK_CLI

The SIDEWALK_CLI enables CLI compatible with sid_dut sample.

To get list of supported CLI commands, you can use `sid help`.

Minimal Sidewalk libraries
==========================

To save ROM space, Sidewalk minimal libraries supporting only BLE link mask could be selected byt the Kconfig

CONFIG_SIDEWALK_LM_BLE_ONLY

Bootloader and Device Firmware Update (DFU)
===========================================

MCUboot is configured to have two banks of memory for an application.

For more information on bootloaders and delivery options for the updated images, see `Bootloader and DFU solutions for NCS`_.


DFU services
------------

To test the Device Firmware Update, follow the Testing Device Firmware Update (DFU) subsection in :ref:`template_testing`.

If a new, correct image is found, the bootloader can only start the application that is placed in the first partition and exchange the application from the second partition.
It may take a few seconds.

Building and running
********************

This sample can be found under :file:`samples/template`.

.. note::
   Before you flash you Sidewalk sample, make sure you completed the following:

      * You downloaded the Sidewalk repository and updated west according to the :ref:`dk_building_sample_app` section.
      * You provisioned your device during the :ref:`setting_up_sidewalk_product`.

   This step needs to be completed only once.
   You do not have to repeat it on every sample rebuild.

To build the sample, follow the steps in the `Building and programming an application`_ documentation.

.. _template_testing:

Testing
=======

See `Testing and debugging an application`_ for information on testing and debugging in the nRF Connect SDK.

After successfully building the sample and flashing manufacturing data, the sample is ready to use.
To refresh the logs, restart the program by pressing the :guilabel:`RESET` button on your development kit.
You should see the following output:

   .. code-block:: console

       *** Booting Zephyr OS build v3.2.99-ncs2 ***
       ----------------------------------------------------------------
       sidewalk             v1.14.3-1-g1232aabb
       nrf                  v2.3.0
       zephyr               v3.2.99-ncs2
       ----------------------------------------------------------------
       sidewalk_fork_point = af5d608303eb03465f35e369ef22ad6c02564ac6
       build time          = 2023-03-14 15:00:00.000000+00:00
       ----------------------------------------------------------------

       [00:00:00.006,225] <inf> sid_template: Sidewalk example started!

Wait for the device to complete the :ref:`automatic_registration_sidewalk_endpoints`.

.. note::
   If you have multiple Echo devices registered under a single Amazon account, only one of those devices will be able to operate as an FSK gateway even if other devices have the same capability.
   If you need to operate multiple FSK gateways, we recommend setting them up under separate Amazon accounts.

.. include:: testing_sample_include.txt


.. _SX1262: https://os.mbed.com/components/SX126xMB2xAS/
