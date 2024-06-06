Notes regaring API Usage                {#apiusage}
========================

There are some restrictions on the [Application Interface](@ref ApplicationInterface)
with respect to the state of the Master instance and the calling context,
which are explained in the following.


## Rules of Thumb

All configuration (`ecrt_slave_config_*()`) has to be done in Linux Process context.
They can be blocking, so take care when holding locks.
After ecrt_master_activate() ing the master,
your application must not alter the Slave configuration.
Instead, update Process Data using
ecrt_domain_queue() and ecrt_domain_process()
or use the asynchronous interface like ecrt_sdo_request_read().
Don't forget to ecrt_master_receive() and ecrt_master_send().
These functions can be called from non-Process context too,
like Xenomai/RTAI applications or custom Kernel modules.

## Master state

The first distinction of cases is whether ecrt_master_activate() has been called or not.
Before ecrt_master_activate() (or after ecrt_master_deactivate()),
the master is in Idle mode.
Sending and receiving EtherCAT frames will be done by the master itself,
the Application (e.g. you) can configure the Slaves.
After ecrt_master_activate(), the Master switches into Operational (OP) mode.
The Application is now in charge of steering the communication.
Process data can be exchanged under real time constraints.
Altering the Slave configuration is not possible anymore.

| Tag           | Description |
|---------------|-----------------------------------------------------------------------------------------|
| `master_op`   | Master must be in Operational State, so after `ecrt_master_activate()` has been called. |
| `master_idle` | Master must be in Idle State, so before `ecrt_master_activate()` has been called.       |
| `master_any`  | Master can be in Idle or Operational State.                                             |


## Allowed Context

The second distinction of cases is the calling context of the caller,
which means how the Application is run.
Most of the functions of the [Application Interface](@ref ApplicationInterface)
have to acquire locks or allocate memory,
so they are potentially sleeping.
They are tagged as `blocking`.
Sleeping is not allowed in all contexts,
for instance when using Xenomai/RTAI or a Kernel timer.
Only a very limited set of functions can be called from any context,
marked as `rt_safe`.
They do not allocate memory.


| Tag        | Description |
|------------|-------------|
| `rt_safe`  | Realtime Context (RT Userspace, atomic/softirq context in Kernel, Xenomai/RTAI RT Task) safe. |
| `blocking` | Linux Process context only (Userspace or Kernel), might block. |
