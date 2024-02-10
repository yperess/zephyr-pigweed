/* Copyright (c) 2024 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "hello.h"
#include "pw_log/log.h"

namespace {

TEST(TrackDatabase, EmptyTrackDatabaseReturnsNotFoundFromFindByTrackId) {
  app::TrackDatabase<0> database({});
  for (int track_id : {0, 1, 2, 3, 4, 10, 93, 1024}) {
    EXPECT_EQ(pw::Status::NotFound(),
              database.FindTrackById(track_id).status());
  }
}

TEST(TrackDatabase, CanFindTrackThatIsInDatabase) {
  pw::Result<const app::Track*> track;
  app::TrackDatabase<5> database(app::CannedTracks());

  track = database.FindTrackById(1);
  EXPECT_TRUE(track.ok());
  EXPECT_EQ(track.value()->id, 1);
  EXPECT_STREQ(track.value()->title.c_str(), "Money for Mumbling Monkeys");
  EXPECT_STREQ(track.value()->artist_name.c_str(), "Dire Music");
  EXPECT_EQ(track.value()->year, 1974);

  track = database.FindTrackById(42);
  EXPECT_TRUE(track.ok());
  EXPECT_EQ(track.value()->id, 42);
  EXPECT_STREQ(track.value()->title.c_str(),
               "Life, the Universe, and Everything");
  EXPECT_STREQ(track.value()->artist_name.c_str(), "Douglas Adams");
  EXPECT_EQ(track.value()->year, 1952);
}

TEST(TrackDatabase, CannotFindTrackThatIsNotInDatabase) {
  app::TrackDatabase<5> database(app::CannedTracks());
  auto track = database.FindTrackById(-1);

  EXPECT_EQ(pw::Status::NotFound(), track.status());
}

}  // namespace
