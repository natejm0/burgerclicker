#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// target
int target_health = 50;
   
// gun
int damage, mag_size, max_ammo_loaded, ammo;

void reload() {
   if (mag_size > 0) {
      int ammo_to_add = max_ammo_loaded - ammo;
      
      ammo += ammo_to_add;
      mag_size -= ammo_to_add;
      printf("You reloaded your gun! (%d/%d)\n", ammo, mag_size);
   }
   else {
      printf("You have no more ammo!\n");
   }
}

void fire() {
   ammo -= 1;
   target_health -= damage;   
      
   if (target_health > 0) {
      printf("You shoot the target and deal %d damage leaving the target at %d heatlh!\n", damage, target_health);
      printf("Ammo: %d / %d\n", ammo, mag_size);
   }
   else {
      printf("The target is dead!\n");
   }
}

int main() {
   
   printf("Fire your gun\n");
   
   damage = 5;
   mag_size = 20;
   max_ammo_loaded = 6;
   ammo = 6;
   
   char user_input = 0;

   while(true) {
      
      printf("");
      user_input = getc(stdin);
      
      if (target_health > 0) {
         
         if (user_input == 'f') {
            
            if (ammo > 0) { 
               fire();
            }
            else {
               printf("You need to reload!\n");
            }

         }
         else if (user_input == 'r') {
            
            if (ammo < max_ammo_loaded) {
               reload();
            }
            else {
               printf("Your ammo is already fully loaded!\n");
            }

         }
      }   
      else {
         
         printf("");
         user_input = getc(stdin);

         if (user_input == 'f') {
            printf("The target is dead already!\n");
         }
         else if (user_input == 'r') {
            
            if (ammo < max_ammo_loaded) {
               reload();
            }
            else {
               printf("Your ammo is already fully loaded!\n");
            }

         }
      }
   }

   return 0;
}