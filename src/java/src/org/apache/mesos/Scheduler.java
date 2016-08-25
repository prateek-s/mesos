/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.mesos;

import org.apache.mesos.Protos.*;

import java.util.List;


/**
 * Callback interface to be implemented by frameworks'
 * schedulers. Note that only one callback will be invoked at a time,
 * so it is not recommended that you block within a callback because
 * it may cause a deadlock.
 * <p>
 * Each callback includes a reference to the scheduler driver that was
 * used to run this scheduler. The reference will not change for the
 * duration of a scheduler (i.e., from the point you do {@link
 * SchedulerDriver#start} to the point that {@link
 * SchedulerDriver#join} returns). This is intended for convenience so
 * that a scheduler doesn't need to store a reference to the driver
 * itself.
 */
public interface Scheduler {
  /**
   * Invoked when the scheduler successfully registers with a Mesos
   * master. A unique ID (generated by the master) used for
   * distinguishing this framework from others and MasterInfo
   * with the IP and port of the current master are provided as arguments.
   *
   * @param driver      The scheduler driver that was registered.
   * @param frameworkId The framework ID generated by the master.
   * @param masterInfo  Info about the current master, including IP and port.
   *
   * @see SchedulerDriver
   * @see FrameworkID
   * @see MasterInfo
   */
  void registered(SchedulerDriver driver,
                  FrameworkID frameworkId,
                  MasterInfo masterInfo);

  /**
   * Invoked when the scheduler re-registers with a newly elected Mesos master.
   * This is only called when the scheduler has previously been registered.
   * MasterInfo containing the updated information about the elected master
   * is provided as an argument.
   *
   * @param driver      The driver that was re-registered.
   * @param masterInfo  The updated information about the elected master.
   *
   * @see SchedulerDriver
   * @see MasterInfo
   */
  void reregistered(SchedulerDriver driver, MasterInfo masterInfo);

  /**
   * Invoked when resources have been offered to this framework. A
   * single offer will only contain resources from a single slave.
   * Resources associated with an offer will not be re-offered to
   * _this_ framework until either (a) this framework has rejected
   * those resources (see {@link SchedulerDriver#launchTasks}) or (b)
   * those resources have been rescinded (see {@link Scheduler#offerRescinded}).
   * Note that resources may be concurrently offered to more than one
   * framework at a time (depending on the allocator being used). In
   * that case, the first framework to launch tasks using those
   * resources will be able to use them while the other frameworks
   * will have those resources rescinded (or if a framework has
   * already launched tasks with those resources then those tasks will
   * fail with a TASK_LOST status and a message saying as much).
   *
   * @param driver  The driver that was used to run this scheduler.
   * @param offers  The resources offered to this framework.
   *
   * @see SchedulerDriver
   * @see Offer
   */
  void resourceOffers(SchedulerDriver driver, List<Offer> offers);

  void cloudInfo(SchedulerDriver driver,   double e_cost ,
		 double e_mttf ,
		 double current_cost ,
		 double current_mttf) ;

  void terminationWarning(SchedulerDriver driver,
			  List<InverseOffer> inverse_offers,
			  double warning_time_seconds) ;

  
  /**
   * Invoked when an offer is no longer valid (e.g., the slave was
   * lost or another framework used resources in the offer). If for
   * whatever reason an offer is never rescinded (e.g., dropped
   * message, failing over framework, etc.), a framework that attempts
   * to launch tasks using an invalid offer will receive TASK_LOST
   * status updates for those tasks (see {@link #resourceOffers}).
   *
   * @param driver  The driver that was used to run this scheduler.
   * @param offerId The ID of the offer that was rescinded.
   *
   * @see SchedulerDriver
   * @see OfferID
   */
  void offerRescinded(SchedulerDriver driver, OfferID offerId);

  /**
   * Invoked when the status of a task has changed (e.g., a slave is
   * lost and so the task is lost, a task finishes and an executor
   * sends a status update saying so, etc). If implicit
   * acknowledgements are being used, then returning from this
   * callback _acknowledges_ receipt of this status update! If for
   * whatever reason the scheduler aborts during this callback (or
   * the process exits) another status update will be delivered (note,
   * however, that this is currently not true if the slave sending the
   * status update is lost/fails during that time). If explicit
   * acknowledgements are in use, the scheduler must acknowledge this
   * status on the driver.
   *
   * @param driver The driver that was used to run this scheduler.
   * @param status The status update, which includes the task ID and status.
   *
   * @see SchedulerDriver
   * @see TaskStatus
   */
  void statusUpdate(SchedulerDriver driver, TaskStatus status);

  /**
   * Invoked when an executor sends a message. These messages are best
   * effort; do not expect a framework message to be retransmitted in
   * any reliable fashion.
   *
   * @param driver      The driver that received the message.
   * @param executorId  The ID of the executor that sent the message.
   * @param slaveId     The ID of the slave that launched the executor.
   * @param data        The message payload.
   *
   * @see SchedulerDriver
   * @see ExecutorID
   * @see SlaveID
   */
  void frameworkMessage(SchedulerDriver driver,
                        ExecutorID executorId,
                        SlaveID slaveId,
                        byte[] data);

  /**
   * Invoked when the scheduler becomes "disconnected" from the master
   * (e.g., the master fails and another is taking over).
   *
   * @param driver  The driver that was used to run this scheduler.
   *
   * @see SchedulerDriver
   */
  void disconnected(SchedulerDriver driver);

  /**
   * Invoked when a slave has been determined unreachable (e.g.,
   * machine failure, network partition). Most frameworks will need to
   * reschedule any tasks launched on this slave on a new slave.
   *
   * NOTE: This callback is not reliably delivered. If a host or
   * network failure causes messages between the master and the
   * scheduler to be dropped, this callback may not be invoked.
   *
   * @param driver  The driver that was used to run this scheduler.
   * @param slaveId The ID of the slave that was lost.
   *
   * @see SchedulerDriver
   * @see SlaveID
   */
  void slaveLost(SchedulerDriver driver, SlaveID slaveId);

  /**
   * Invoked when an executor has exited/terminated. Note that any
   * tasks running will have TASK_LOST status updates automagically
   * generated.
   *
   * NOTE: This callback is not reliably delivered. If a host or
   * network failure causes messages between the master and the
   * scheduler to be dropped, this callback may not be invoked.
   *
   * @param driver      The driver that was used to run this scheduler.
   * @param executorId  The ID of the executor that was lost.
   * @param slaveId     The ID of the slave that launched the executor.
   * @param status      The exit status of the executor.
   *
   * @see SchedulerDriver
   * @see ExecutorID
   * @see SlaveID
   * @see Status
   */
  void executorLost(SchedulerDriver driver,
                    ExecutorID executorId,
                    SlaveID slaveId,
                    int status);

  /**
   * Invoked when there is an unrecoverable error in the scheduler or
   * driver. The driver will be aborted BEFORE invoking this callback.
   *
   * @param driver  The driver that was used to run this scheduler.
   * @param message The error message.
   *
   * @see SchedulerDriver
   */
  void error(SchedulerDriver driver, String message);
}
