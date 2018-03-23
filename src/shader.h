#import <Foundation/Foundation.h>
#import <GL/glew.h>

@interface Shader : NSObject {
  GLuint program;
}

- (id) init;
- (void) use;
@end
