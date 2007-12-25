/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_DEFAULT_PEER_STORAGE_H_
#define _D_DEFAULT_PEER_STORAGE_H_

#include "PeerStorage.h"
#include "BtContext.h"
#include "Option.h"
#include "Logger.h"
#include "BtRuntime.h"

#define MAX_PEER_LIST_SIZE 60
#define MAX_PEER_ERROR 5

class DefaultPeerStorage : public PeerStorage {
private:
  BtContextHandle btContext;
  const Option* option;
  Peers peers;
  int32_t maxPeerListSize;
  Logger* logger;
  BtRuntimeHandle btRuntime;
  int64_t removedPeerSessionDownloadLength;
  int64_t removedPeerSessionUploadLength;

  bool isPeerAlreadyAdded(const PeerHandle& peer);
public:
  DefaultPeerStorage(BtContextHandle btContext, const Option* option);
  virtual ~DefaultPeerStorage();

  void setBtRuntime(const BtRuntimeHandle& btRuntime) {
    this->btRuntime = btRuntime;
  }
  BtRuntimeHandle getBtRuntime() const { return btRuntime; }

  virtual bool addPeer(const PeerHandle& peer);

  int32_t countPeer() const;

  virtual PeerHandle getUnusedPeer();

  PeerHandle getPeer(const string& ipaddr, int32_t port) const;

  virtual void addPeer(const Peers& peers);

  virtual const Peers& getPeers();

  virtual bool isPeerAvailable();

  virtual Peers getActivePeers();

  virtual TransferStat calculateStat();

  virtual void returnPeer(const PeerHandle& peer);

  void setMaxPeerListSize(int32_t size) { this->maxPeerListSize = size; }
 
  int32_t getMaxPeerListSize() const { return maxPeerListSize; }

  void deleteUnusedPeer(int32_t delSize);
  
  void onErasingPeer(const PeerHandle& peer);
};

#endif // _D_DEFAULT_PEER_STORAGE_H_
