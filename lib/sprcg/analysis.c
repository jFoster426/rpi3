#ifndef analysis_c
#define analysis_c

unsigned short maxVal(unsigned short d[]) {
	// returns the bin number of the max value
	short i, m = 0, n;
	for(i = 0; i < N_WAVE / 2; i++) {
		if(m > d[i]) {
			m = d[i];
			n = i;
		}
	}
	return i;
}

short findNumOfPeaks(unsigned short n, unsigned short st) {
	unsigned short i, b, s, f;
	for(i = 0; i < n; i++) {
		b = maxVal(fftout);
		if(b < AMP_THRESH) return i; // 
		for(f = b + 1, f < N_WAVE / 2; f++)
			if(fftout[f] < fftout[f + 1])
				goto fin;
		fin:
		for(s = b - 1, s >= 0; s--)
			if(fftout[s] < fftout[s - 1])
				goto com;
		com:
		short w = f - s;
		if((fftout[b] / (b - s)) > st || (fftout[b] / (f - b)) > st) {
			fftpks[csamp][i].pos = b;
			fftpks[csamp][i].mag = fftout[b];
			order[i] = b;
		}
		else
			i--;
	}
	return -1;
}

void interpolatePeaks(unsigned short pA, float *pB, unsigned short pC, float *pos) {
	float a = (pA / 2.0) + -pB + (pC / 2.0),
	b = ((pA * 5.0) / 2.0) + (pB * -4) + ((pC * 3.0) / 2.0),
	c = (pA * 3.0) + (pB * -3.0) + pC;
	*pos = b / (2.0 * a);
	*pB = ((4.0 * a * c) - b * b) / (4.0 * a);
	// interpolatePeaks(fftout[i-1], fftpks[i].mag, fftout[i+1], fftpks[i].pos);
	// fftpks[i].pos += i;
}

void orderByPosition() {
	short i, j, jVal;
	float tmp;
	for(i = 0; i < MAX_PEAKS; i++) {
        for(j = i; j < MAX_PEAKS; j++) {
            if(fftpks[csamp][j].pos < fftpks[csamp][i].pos) {
                tmp = fftpks[csamp][j].pos;
		        fftpks[csamp][j].pos = fftpks[csamp][i].pos;
		        fftpks[csamp][i].pos = tmp;
				tmp = fftpks[csamp][j].mag;
		        fftpks[csamp][j].mag = fftpks[csamp][i].mag;
		        fftpks[csamp][i].mag = tmp;
            }
        }
	}
}

void findVelocity() {
	if(csamp == 0) return;
	short i, j;
	float dif;
	for(i = 0; i < MAX_PEAKS; i++) {
		for(j = 0; j < MAX_PEAKS; j++) {
			if(dif > abs(fftpks[csamp-1][i].pos - fftpks[csamp][j].pos)
				dif = abs(fftpks[csamp-1][i].pos - fftpks[csamp][j].pos);
		}
		if(dif <= POS_THRESH) {
			fftvel[csamp-1][i].pos = fftpks[csamp-1][i];
			fftvel[csamp-1][i].vel = dif / SAMP_RATE;
		}
		else
			fftvel[csamp-1][i].pos = 0;
	}
}

#endif