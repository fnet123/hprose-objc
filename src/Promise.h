/**********************************************************\
|                                                          |
|                          hprose                          |
|                                                          |
| Official WebSite: http://www.hprose.com/                 |
|                   http://www.hprose.org/                 |
|                                                          |
\**********************************************************/
/**********************************************************\
 *                                                        *
 * Promise.h                                              *
 *                                                        *
 * Promise header for Objective-C.                        *
 *                                                        *
 * LastModified: May 20, 2016                             *
 * Author: Ma Bingyao <andot@hprose.com>                  *
 *                                                        *
\**********************************************************/

#import <Foundation/Foundation.h>

@interface NSArray<ObjectType> (NSArrayFunctional)

- (void) each:(id (^)(ObjectType element, NSUInteger index))handler;
- (BOOL) every:(BOOL (^)(ObjectType element, NSUInteger index))handler;
- (BOOL) some:(BOOL (^)(ObjectType element, NSUInteger index))handler;
- (NSArray<ObjectType> *) filter:(BOOL (^)(ObjectType element, NSUInteger index))handler;
- (NSArray *) map:(id (^)(ObjectType element, NSUInteger index))handler;
- (id) reduce:(id (^)(id prev, ObjectType element, NSUInteger index))handler;
- (id) reduce:(id (^)(id prev, ObjectType element, NSUInteger index))handler init:(id)value;
- (id) reduceRight:(id (^)(id prev, ObjectType element, NSUInteger index))handler;
- (id) reduceRight:(id (^)(id prev, ObjectType element, NSUInteger index))handler init:(id)value;

@end

typedef enum {
    PENDING = 0,
    FULFILLED = 1,
    REJECTED = 2
} PromiseState;

@interface Promise : NSObject {
@private
    NSMutableArray *_subscribers;
}

@property (readonly) PromiseState state;
@property (readonly) id result;
@property (readonly) id reason;

- (id) init:(id (^)(void)) computation;

+ (Promise *) promise;
+ (Promise *) promise:(id (^)(void))computation;
+ (Promise *) value:(id)result;
+ (Promise *) error:(id)reason;
+ (Promise *) delayed:(NSTimeInterval)duration with:(id)value;
+ (Promise *) delayed:(NSTimeInterval)duration block:(id (^)(void))computation;
+ (Promise *) sync:(id (^)(void))computation;
+ (BOOL) isPromise:(id)value;
+ (Promise *) toPromise:(id)value;
+ (Promise *) all:(NSArray *)array;
+ (Promise *) race:(NSArray *)array;
+ (Promise *) any:(NSArray *)array;
+ (Promise *) each:(id (^)(id element, NSUInteger index))handler with:(NSArray *)array;
+ (Promise *) every:(BOOL (^)(id element, NSUInteger index))handler with:(NSArray *)array;
+ (Promise *) some:(BOOL (^)(id element, NSUInteger index))handler with:(NSArray *)array;
+ (Promise *) filter:(BOOL (^)(id element, NSUInteger index))handler with:(NSArray *)array;
+ (Promise *) map:(id (^)(id element, NSUInteger index))handler with:(NSArray *)array;
+ (Promise *) reduce:(id (^)(id prev, id element, NSUInteger index))handler with:(NSArray *)array;
+ (Promise *) reduce:(id (^)(id prev, id element, NSUInteger index))handler with:(NSArray *)array init:(id)value;
+ (Promise *) reduceRight:(id (^)(id prev, id element, NSUInteger index))handler with:(NSArray *)array;
+ (Promise *) reduceRight:(id (^)(id prev, id element, NSUInteger index))handler with:(NSArray *)array init:(id)value;

- (void) resolve:(id)result;
- (void) reject:(id)reason;
- (Promise *) then:(id (^)(id))onfulfill catch:(id (^)(id))onreject;
- (Promise *) then:(id (^)(id))onfulfill;
- (Promise *) last:(void (^)(id))onfulfill catch:(void (^)(id))onreject;
- (Promise *) last:(void (^)(id))onfulfill;
- (void) done:(void (^)(id))onfulfill fail:(void (^)(id))onreject;
- (void) done:(void (^)(id))onfulfill;
- (Promise *) catch:(id (^)(id))onreject with:(BOOL (^)(id))test;
- (Promise *) catch:(id (^)(id))onreject;
- (void) fail:(void (^)(id))onreject;
- (Promise *) whenComplete:(void (^)())action;
- (Promise *) complete:(id (^)(id))oncomplete;
- (void) always:(void (^)(id))oncomplete;
- (void) fill:(Promise *)promise;
- (Promise *) timeout:(NSTimeInterval)duration with:(id)reason;
- (Promise *) timeout:(NSTimeInterval)duration;
- (Promise *) delay:(NSTimeInterval)duration;
- (Promise *) tap:(void (^)(id))onfulfilledSideEffect;

- (Promise *) all;
- (Promise *) race;
- (Promise *) any;
- (Promise *) each:(id (^)(id element, NSUInteger index))handler;
- (Promise *) every:(BOOL (^)(id element, NSUInteger index))handler;
- (Promise *) some:(BOOL (^)(id element, NSUInteger index))handler;
- (Promise *) filter:(BOOL (^)(id element, NSUInteger index))handler;
- (Promise *) map:(id (^)(id element, NSUInteger index))handler;
- (Promise *) reduce:(id (^)(id prev, id element, NSUInteger index))handler;
- (Promise *) reduce:(id (^)(id prev, id element, NSUInteger index))handler init:(id)value;
- (Promise *) reduceRight:(id (^)(id prev, id element, NSUInteger index))handler;
- (Promise *) reduceRight:(id (^)(id prev, id element, NSUInteger index))handler init:(id)value;

@end

