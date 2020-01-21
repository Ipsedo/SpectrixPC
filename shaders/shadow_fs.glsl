out float fragmentdepth;

void main(){
    // Pas vraiment nécessaire, OpenGL le fait de toute façon
    fragmentdepth = gl_FragCoord.z;
}
