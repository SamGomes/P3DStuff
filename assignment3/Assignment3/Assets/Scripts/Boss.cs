using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss : Enemy
{


    // Update is called once per frame
    void LateUpdate()
    {
        if (this.isDead)
            return;

        if (life <= 0)
        {
            this.GetComponent<Animator>().SetBool("bossKill", true);
        }


    }

}
