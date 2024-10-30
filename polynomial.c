#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<jansson.h>

long long decode_base(const char *value, int base){
    return strtoll(value, NULL, base);
}

long long lagrange_interpolation(int x[], long long y[], int k){
    long long result = 0;
    for(int i=0;i<k;i++){
        long long term = y[i];
        for(int j=0;j<k;j++){
            if(i!=j){
                term *= -x[j];
                term /= (x[i]-x[j];)
            }
        }
        result += term;
    }
    return result;
}

void parse_json_and_cal_const(cosnt car *filename){
    json_error_t error;
    json_t *root = json_load_file(filename, 0, &error);
    if(!root){
        fprintf(stderr, "Error parsing JSON: %s\n",error.text);
        return;
    }

    json_t *keys = json_object_get(root, "keys");
    int n = json_integer_value(json_object_get(keys, "n"));
    int k =json_integer_value(json_object_get(keys, "k"));
    intx[n];
    long long y[n];

    const char *key;
    json_t *value;
    int count = 0;
    json_object_foreach(root, key, value){
        if(strcmp(key, "keys")!=0){
            x[count]= atoi(key);
            int base = json_integer_value(json_object_get(value, "base"));
            const char *encode_y = json_string_value(json_object_get(value, "value"));
            y[count] = decode_base(encode_y, base);
            count++;
        }
    }

    long long secret = lagrange_interpolation(x, y, k);
    printf("The secret constant term (c) is: %lld\n", secret);

    json_decref(root);
}

int main(){
    const char *filename1="testcase1.json";
    const char *filename2="testcase2.json";

    printf("testcase 1: \n");
    parse_json_and_cal_const(filename1);

    printf("testcase 2: \n");
    parse_json_and_cal_const(filename2);

    return 0;
}