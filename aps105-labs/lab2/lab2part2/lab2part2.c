#include <stdio.h>
#include <math.h>

int main(){
    double xCoordinate;
    double yCoordinate;

    printf("Enter the x-coordinate in floating point: ");
    scanf("%lf\n", &xCoordinate);
    printf("Enter the y-coordinate in floating point: ");
    scanf("%lf\n", &yCoordinate);

    xCoordinate = rint(xCoordinate*100)/100;
    yCoordinate = rint(yCoordinate*100)/100;

    if (xCoordinate > 0 && yCoordinate > 0){
        printf("\n(%.2lf, %.2lf) is in quadrant I.", xCoordinate, yCoordinate);
    }
    else if (xCoordinate < 0 && yCoordinate > 0){
        printf("\n(%.2lf, %.2lf) is in quadrant II.", xCoordinate, yCoordinate);
    }
    else if (xCoordinate < 0 && yCoordinate < 0){
        printf("\n(%.2lf, %.2lf) is in quadrant III.", xCoordinate, yCoordinate);
    }
    else if (xCoordinate > 0 && yCoordinate < 0){
        printf("\n(%.2lf, %.2lf) is in quadrant IV.", xCoordinate, yCoordinate);
    }
    else if (xCoordinate == 0 && yCoordinate == 0){
        printf("\n(%.2lf, %.2lf) is at the origin.", xCoordinate, yCoordinate);
    }
    else if (xCoordinate == 0 && (yCoordinate < 0 || yCoordinate > 0)){
        printf("\n(%.2lf, %.2lf) is on the y axis.", xCoordinate, yCoordinate);
    }
    else if ((xCoordinate < 0 || xCoordinate > 0) && yCoordinate == 0){
        printf("\n(%.2lf, %.2lf) is on the x axis.", xCoordinate, yCoordinate);
    }
    return 0;
}