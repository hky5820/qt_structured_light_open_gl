#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 vPos;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 pPos;
uniform int mod;

void main()
{
        // linearly interpolate between both textures (80% container, 20% awesomeface)
        float PI = 3.1415926535;
        vec3 vertexPos = vPos.xyz;
        vec3 pvRazor = vertexPos - pPos;
        vec3 pcRzaor = -pPos;
        normalize(pvRazor);
        normalize(pcRzaor);

        float dotRes = dot(pvRazor, pcRzaor);
        float rad = acos(dotRes);
        float angle = rad * 180.0 / PI;

        if(mod == 0){
            FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
        }
        else if(mod == 1){
            if( vPos.x < 0.0){
                FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
            }
            else{
                FragColor = vec4(0.0,0.0,0.0,1.0);
            }
        }
        else if(mod ==2){
            int i = 0;
            float length = 1.0/ pow(float(2), mod-1);
            while(i < 4){
                if(i %2 ==0){
                    if(vPos.x > (-1.0 + length * i)&& vPos.x < (-0.5+ length * i)){
                        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
                    }
                }
                else{
                    if(vPos.x > (-1.0 + length * i)&& vPos.x < (-0.5+ length * i)){
                          FragColor = vec4(0.0,0.0,0.0,1.0);
                    }

                }
                i++;
            }
        }
        else if(mod == 3){
            int i = 0;
            float length = 1.0/ pow(float(2), mod-1);
            while(i <  pow(float(2), mod)){
                if(i %2 ==0){
                    if(vPos.x > (-1.0 + length * i)&& vPos.x < (-0.5+ length * i)){
                        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
                    }
                }
                else{
                    if(vPos.x > (-1.0 + length * i)&& vPos.x < (-0.5+ length * i)){
                          FragColor = vec4(0.0,0.0,0.0,1.0);
                    }

                }
                i++;
            }
        }


}
