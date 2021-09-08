#ifndef CONSTANT_HEADER
#define CONSTANT_HEADER

//? #version 460 core

const uint positionAttribLocation = 0U;
const uint normalAttribLocation = 1U;
const uint tangentAttribLocation = 2U;
const uint texcoordAttribLocation = 3U;
const uint colorAttribLocation = 4U;
const uint jointsAttribLocation = 5U;
const uint weightsAttribLocation = 6U;

const uint postionAttribFlag = (1U << positionAttribLocation);
const uint normalAttribFlag = (1U << normalAttribLocation);
const uint tangentAttribFlag = (1U << tangentAttribLocation);
const uint texcoordAttribFlag = (1U << texcoordAttribLocation);
const uint colorAttribFlag = (1U << colorAttribLocation);
const uint jointsAttribFlag = (1U << jointsAttribLocation);
const uint weightsAttribFlag = (1U << weightsAttribLocation);

#endif