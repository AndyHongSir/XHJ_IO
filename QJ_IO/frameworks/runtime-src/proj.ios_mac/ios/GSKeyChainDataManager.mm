//
//  GSKeyChainDataManager.m
//  keychaintest
//
//  Created by Apple on 16/8/2.
//  Copyright © 2016年 张国森. All rights reserved.
//

#include "GSKeyChainDataManager.h"
#import "GSKeyChain.h"

static const char *  KEY_IN_KEYCHAIN_UUID = "唯一识别的KEY_UUID";
static const char *  KEY_UUID = "唯一识别的key_uuid";

void GSKeyChainDataManager::saveUUID(const char * UUID){
    NSMutableDictionary *usernamepasswordKVPairs = [NSMutableDictionary dictionary];
    [usernamepasswordKVPairs setObject: [NSString stringWithUTF8String:UUID] forKey:[NSString stringWithUTF8String:KEY_UUID]];
    
    [GSKeyChain save:[NSString stringWithUTF8String:KEY_IN_KEYCHAIN_UUID]  data:usernamepasswordKVPairs];

}
const char * GSKeyChainDataManager::readUUID(){
#if TARGET_IPHONE_SIMULATOR//模拟器
     NSString *deviceUUID = [[UIDevice currentDevice].identifierForVendor UUIDString];
    return [deviceUUID UTF8String];
#elif TARGET_OS_IPHONE//真机
    NSMutableDictionary *usernamepasswordKVPair = (NSMutableDictionary *)[GSKeyChain load:[NSString stringWithUTF8String:KEY_IN_KEYCHAIN_UUID] ];
    
    return [[usernamepasswordKVPair objectForKey:[NSString stringWithUTF8String:KEY_UUID] ] UTF8String];
#endif
    
}
void GSKeyChainDataManager::deleteUUID(){
    [GSKeyChain delete:[NSString stringWithUTF8String:KEY_IN_KEYCHAIN_UUID] ];
}


