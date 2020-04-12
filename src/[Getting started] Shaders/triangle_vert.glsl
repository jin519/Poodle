// 가장 첫 줄엔 무조건 버전을 적는다.
#version 460 core

layout (location = 0) in vec3 pos;

void main()
{
    gl_Position = vec4(pos, 1.f);
}