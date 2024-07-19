FakeEtherCAT Library                        {#libfakeethercat}
====================

Libfakeethercat is a userspace library which has the same API as
the EtherCAT master interface library libethercat.
Libfakeethercat can be used to spin up your RT application in a dry-run mode,
without any master configured or slaves attached.
Furthermore, it is possible to emulate EtherCAT slaves on process data level
by running two applications back to back.

## Supported features

Currently, only a very limited subset of libethercat functionality is supported:

 - Creating master and domain instances
 - Activating master, `send`/`receive`.
 - Processing and queuing domains
 - Configuring PDOs
 - Configuring SDOs using `ecrt_slave_config_sdo*`

The SDO config does not do anything,
but when activating the master the SDO config will
be dumped into a JSON file.

ecrt_master_state() and ecrt_domain_state() both return states as if
the bus works without errors.
So currenty, a bus error cannot be simulated.

## How to build

[RtIPC](https://gitlab.com/etherlab.org/rtipc) is needed.
Simply pass `--enable-fakeuserlib` to your `./configure` call
and the library will be built for you.

## How to set up dry run mode

### Redirect library loading

To avoid recompiling your application,
we will use `LD_LIBRARY_PATH` to load `libfakeethercat` instead of `libethercat`.

```sh
# pick a location for an empty directory
export MY_LIB_LOCATION=$HOME/fake_lib64
# create that directory
mkdir -p $MY_LIB_LOCATION
# create a symlink to libfakeethercat
# assuming SOVERSION is 1
# debian users, please use /usr/lib/x86_64-linux-gnu/libfakeethercat.so.1
ln -s /usr/lib64/libfakeethercat.so.1 $MY_LIB_LOCATION/libethercat.so.1
# use MY_LIB_LOCATION to load libraries first
export LD_LIBRARY_PATH=$MY_LIB_LOCATION
# check whether everything is done right
ldd my_application | grep ethercat
    libethercat.so.1 => /home/vh/fake_lib64/libethercat.so.1 (0x00007fa5a5c59000)
```

### Set up FakeEtherCAT Home

RtIPC needs a place to store its configuration.
Set `FAKE_EC_HOMEDIR` environment variabe to a path to an empty directory,
for instance `/tmp/FakeEtherCAT`.
`FAKE_EC_NAME` can be set to a useful name of your application,
default is `FakeEtherCAT`.

```sh
export FAKE_EC_HOMEDIR=/tmp/FakeEtherCAT
rm -rf $FAKE_EC_HOMEDIR
mkdir -p $FAKE_EC_HOMEDIR
```

### Spin up your application

Now it's time to simply launch your application.
You will notice that the PDO configuration will be dumped at stderr.
The path displayed is the path of the RtIPC variable in the following format:
`$FAKE_EC_PREFIX/$MASTER_ID/$DOMAIN_ID/$ALIAS$POSITION/$PDO`.

## How to emulate EtherCAT slaves

Let's say you'd like to build virtual EtherCAT slaves to emulate your field.
Libfakeethercat makes that possible with the help of RtIPC.

### Building a simulator

Your field emulator simply has to swap the sync manager direction setting
(EC_DIR_INPUT and EC_DIR_OUTPUT) in ec_sync_info_t.
Libfakeethercat instances use shared memory, provided by RtIPC,
to exchange process data.
The direction setting decides which instance writes and which reads from
shared memory.

For instance, emulating a digial output works in the following way:
Create another real time application with the same slave information
as your control application.
Then, replace all EC_DIR_INPUT with EC_DIR_OUTPUT and vice versa.
Now, remember to read process data instead of writing it, and vice versa.
So, your EL2004 digital out will be read by your simulating application
and has PDO object 0x1600 ff. configured with Sync Manager 2 as EC_DIR_INPUT.

[EtherLab](https://gitlab.com/etherlab.org/etherlab) will be adapted soon
to provide a convenient way to build an entire simulator using SIMULINK.

### Start your application

First, do all the steps explained above to run your
control application in dry run mode.
Then, in another shell, do the same thing with your simulator,
but do not remove the `FAKE_EC_HOMEDIR` directory and
pick another `FAKE_EC_NAME`.

Carefully watch the PDO configuration on stderr and compare them.
All paths configured as Output on the control application have to
be configured as Input on your simulator and vice versa.
If you use multiple domains and there is a mismatch of the domain IDs,
set `FAKE_EC_DOMAIN_PERMUTATION` to a space-separated list of integers to
permutate the domain IDs of one application.
`FAKE_EC_DOMAIN_PERMUTATION="0 1"` swaps domains 0 and 1, for instance.

Finally, your control application needs to be restarted
so it can find the RtIPC variables which contains the process data of the
simulator.

## Environment variables

 - FAKE_EC_DOMAIN_PERMUTATION: Permutate the domain IDs, useful to match control and simulation applications.
 - FAKE_EC_HOMEDIR: Directory for RtIPC builletin board and SDO json files
 - FAKE_EC_NAME: Will be used for naming RtIPC config and SDO json file
 - FAKE_EC_PREFIX: Prefix for RtIPC variables, useful to run multiple simulators side by side.
