/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/
#pragma once
#include <aws/dms/DatabaseMigrationService_EXPORTS.h>
#include <aws/dms/model/ReplicationTask.h>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace DatabaseMigrationService
{
namespace Model
{
  /**
   * <p/>
   */
  class AWS_DATABASEMIGRATIONSERVICE_API StopReplicationTaskResult
  {
  public:
    StopReplicationTaskResult();
    StopReplicationTaskResult(const AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    StopReplicationTaskResult& operator=(const AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);

    /**
     * <p>The replication task stopped.</p>
     */
    inline const ReplicationTask& GetReplicationTask() const{ return m_replicationTask; }

    /**
     * <p>The replication task stopped.</p>
     */
    inline void SetReplicationTask(const ReplicationTask& value) { m_replicationTask = value; }

    /**
     * <p>The replication task stopped.</p>
     */
    inline void SetReplicationTask(ReplicationTask&& value) { m_replicationTask = value; }

    /**
     * <p>The replication task stopped.</p>
     */
    inline StopReplicationTaskResult& WithReplicationTask(const ReplicationTask& value) { SetReplicationTask(value); return *this;}

    /**
     * <p>The replication task stopped.</p>
     */
    inline StopReplicationTaskResult& WithReplicationTask(ReplicationTask&& value) { SetReplicationTask(value); return *this;}

  private:
    ReplicationTask m_replicationTask;
  };

} // namespace Model
} // namespace DatabaseMigrationService
} // namespace Aws
