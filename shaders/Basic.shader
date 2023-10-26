#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
// layout(location = 0) uniform vec3 position;
// layout(location = 1) in vec3 vcolor;
// layout(location = 1) in vec3 vcolor;

// layout(location = 2) in vec2 texcoord;

out vec3 frag_color;
// out vec2 frag_texcoord;

void main() {
    gl_Position = vec4(position, 1.0);
    // gl_Position = vec4(position.x, position.y, position.z, 1.0);
    // frag_color = vcolor;
    // frag_color = vec3(0.0, 0.0, 0.0);
    frag_color = vec3(0.25, 0.5, 0.75);
    // frag_texcoord = texcoord;
}


#shader fragment
#version 450 core

in vec3 frag_color;
// in vec2 frag_texcoord;

out vec4 outColor;

// uniform sampler2D tex;

void main() {
    // outColor = texture(tex, frag_texcoord) * vec4(frag_color, 1.0);
    outColor = vec4(frag_color, 1.0);
    // outColor = vec4(1.0, 1.0, 1.0, 0.3);
}
