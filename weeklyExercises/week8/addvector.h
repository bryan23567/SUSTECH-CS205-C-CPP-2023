
void addvector(const float *p1, const float *p2, float *result, size_t n);
// void addvector_unloop(const float *p1, const float *p2, float *result, size_t n);
void addvector_avx2(const float *p1, const float *p2, float *result, size_t n);
void addvector_avx2_omp(const float *p1, const float *p2, float *result, size_t n);
void addvector_neon(const float *p1, const float *p2, float *result, size_t n);
void addvector_neon_omp(const float *p1, const float *p2, float *result, size_t n);