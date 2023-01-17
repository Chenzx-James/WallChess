//
//  messagebox.m
//  WallChess
//
//  Created by Chen Zixuan on 1/16/23.
//
 
#include "messagebox.h"
#import <Cocoa/Cocoa.h>
namespace client {
    void messagebox(void /*std::string str*/){
        
//        One way
//        NSAlert *alert = [[NSAlert alloc] init];
//        [alert addButtonWithTitle:@"OK"];
//        [alert addButtonWithTitle:@"Cancel"];
//        [alert setMessageText:@(str.c_str())];
//        [alert runModal];
//        NSAlert *alert = [[NSAlert alloc] init];
//        [alert addButtonWithTitle:@"OK"];
//        [alert addButtonWithTitle:@"Cancel"];
//        alert.messageText = @"Error";
//        alert.informativeText = @"无法打开帮助文件，请确认help.txt在程序目录下";
//        [alert setAlertStyle:NSAlertStyleWarning];
//        NSUInteger action = [alert runModal];
//        if(action == NSAlertFirstButtonReturn) {
//            NSLog(@"defaultButton clicked!");
//        }
//        else if(action == NSAlertSecondButtonReturn) {
//            NSLog(@"alternateButton clicked!");
//        }
//         Another way
        
        CFUserNotificationDisplayNotice(0,
                                        kCFUserNotificationNoDefaultButtonFlag,
                                        NULL, NULL, NULL,
                                        CFSTR("Error"),
                                        CFSTR("无法打开帮助文件，请确认help.txt在程序目录下"),
                                        NULL);
//        CFOptionFlags  result;
//
//        CFUserNotificationDisplayAlert(0,
//                                       kCFUserNotificationNoDefaultButtonFlag,
//                                       NULL, NULL, NULL,
//                                       CFSTR("Title"),
//                                       CFSTR("Message"),
//                                       NULL, NULL, NULL, &result);
        return;
    }
}
