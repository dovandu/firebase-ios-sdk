/*
 * Copyright 2017 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>

#import "Firestore/Source/Remote/FSTDatastore.h"

#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"

NS_ASSUME_NONNULL_BEGIN

@interface FSTMockDatastore : FSTDatastore

/**
 * A count of the total number of requests sent to the watch stream since the beginning of the test
 * case.
 */
@property(nonatomic) int watchStreamRequestCount;

/**
 * A count of the total number of requests sent to the write stream since the beginning of the test
 * case.
 */
@property(nonatomic) int writeStreamRequestCount;

#pragma mark - Watch Stream manipulation.

/** Injects a WatchChange as though it had come from the backend. */
- (void)writeWatchChange:(FSTWatchChange *)change
         snapshotVersion:(const firebase::firestore::model::SnapshotVersion &)snap;

/** Injects a stream failure as though it had come from the backend. */
- (void)failWatchStreamWithError:(NSError *)error;

/** Returns the set of active targets on the watch stream. */
- (NSDictionary<FSTBoxedTargetID *, FSTQueryData *> *)activeTargets;

/** Helper method to expose watch stream state to verify in tests. */
- (BOOL)isWatchStreamOpen;

#pragma mark - Write Stream manipulation.

/**
 * Returns the next write that was "sent to the backend", failing if there are no queued sent
 */
- (NSArray<FSTMutation *> *)nextSentWrite;

/** Returns the number of writes that have been sent to the backend but not waited on yet. */
- (int)writesSent;

/** Injects a write ack as though it had come from the backend in response to a write. */
- (void)ackWriteWithVersion:(const firebase::firestore::model::SnapshotVersion &)commitVersion
            mutationResults:(NSArray<FSTMutationResult *> *)results;

/** Injects a stream failure as though it had come from the backend. */
- (void)failWriteWithError:(NSError *_Nullable)error;

@end

NS_ASSUME_NONNULL_END
