/*
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <QApplication>

#include "rviz/visualizer_app.h"

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define SCREENSHOT_SIGNAL 10
#define SCREENSHOT_OUTPUT_PATH "/home/mkurian/catkin_ws/src/bwi_nodejs_client/public/rviz_bin/"

rviz::VisualizerApp *appHandle = NULL;
static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int alphanumsize = sizeof(alphanum) - 1;

void signal_callback_handler(int signum)
{
   if(signum == SCREENSHOT_SIGNAL){
      if(appHandle != NULL){
        std::string sid;
        for(unsigned int i = 0; i < 35; ++i)
          sid += alphanum[rand() % alphanumsize];
        std::string filename = SCREENSHOT_OUTPUT_PATH + sid + ".png";
        if(!appHandle->takeScreenShotNow(filename)){
          printf("%s\n", "Failed to take screenshot!");
        }
      }
   }
}

int main( int argc, char** argv )
{
  // Register signal and signal handler
  signal(SCREENSHOT_SIGNAL, signal_callback_handler);

  QApplication qapp( argc, argv );
  rviz::VisualizerApp vapp;
  appHandle = &vapp;

  if( vapp.init( argc, argv ))
  {
    return qapp.exec();
  }
  else
  {
    return 1;
  }
}
