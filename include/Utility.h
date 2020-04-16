#pragma once

inline int indexOf(int i, int j, int N) {
  return i * (N+2) + j;
}

inline int indexOfPressure(int i, int j, int N) {
  return i * (N+2) + j;
}

inline int indexOfVelocityU(int i, int j, int N) {
  return i * (N+1) + j;
}

inline int indexOfVelocityV(int i, int j, int N) {
  return i * (N+2) + j;
}

inline float linearInterpolate2D(float u, float v, float ll, float lr, float ul, float ur) {
  return (1-v) * ((1-u) * ll + u * lr) + v * ((1-u) * ul + u * ur);
}

inline void setBoundary(int type, float *quantity, int N) {
  for(int i = 1;i <= N;++i) {
    quantity[indexOf(0, i, N)]    = type==1?-quantity[indexOf(1, i, N)] : quantity[indexOf(1, i, N)];
    quantity[indexOf(N+1, i, N)]  = type==1?-quantity[indexOf(N, i, N)] : quantity[indexOf(N, i, N)];
    quantity[indexOf(i, 0, N)]    = type==2?-quantity[indexOf(i, 1, N)] : quantity[indexOf(i, 1, N)];
    quantity[indexOf(i, N+1, N)]  = type==2?-quantity[indexOf(i, N, N)] : quantity[indexOf(i, N, N)];
  }
  quantity[indexOf(0, 0, N)]      = 0.5f * (quantity[indexOf(0, 1, N)] + quantity[indexOf(1, 0, N)]);
  quantity[indexOf(N+1, 0, N)]    = 0.5f * (quantity[indexOf(N+1, 1, N)] + quantity[indexOf(N, 0, N)]);
  quantity[indexOf(0, N+1, N)]    = 0.5f * (quantity[indexOf(1, N+1, N)] + quantity[indexOf(0, N, N)]);
  quantity[indexOf(N+1, N+1, N)]  = 0.5f * (quantity[indexOf(N, N+1, N)] + quantity[indexOf(N+1, N, N)]);
}

inline void setUBoundary(float *u, int N) {
  for(int i = 1;i <= N;++i) {
    u[indexOfVelocityU(0, i, N)] = 0.0f;
    u[indexOfVelocityU(N, i, N)] = 0.0f;
  }
  for(int i = 0;i <= N;++i) {
    u[indexOfVelocityU(i, 0, N)] = u[indexOfVelocityU(i, 1, N)];
    u[indexOfVelocityU(i, N+1, N)] = u[indexOfVelocityU(i, N, N)];
  }
}

inline void setVBoundary(float *v, int N) {
  for(int i = 1;i <= N;++i) {
    v[indexOfVelocityU(i, 0, N)] = 0.0f;
    v[indexOfVelocityU(i, N, N)] = 0.0f;
  }
  for(int i = 0;i <= N;++i) {
    v[indexOfVelocityU(N+1, i, N)] = v[indexOfVelocityV(N, i, N)];
    v[indexOfVelocityV(0, i, N)] = v[indexOfVelocityV(1, i, N)];
  }
}

inline bool isInGrid(int x, int y, int xb, int yb) {
  return x>=0&&y>=0&&x<xb&&y<yb;
}
