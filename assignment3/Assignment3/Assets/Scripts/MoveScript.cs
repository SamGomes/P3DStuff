using UnityEngine;
using System;

public class MoveScript : MonoBehaviour
{
    public int speed;
    public GameObject playerBody;
    public int crouch;
    
    void FixedUpdate()
    {
        float moveHorizontal = Input.GetAxis("Horizontal"); //move up/down
        float moveVertical = Input.GetAxis("Vertical"); //move left/right
        float moveUp = Input.GetKeyDown("q")? 20 : 0; //jump
        float crouchFactor = 10; //crouch
        if (Input.GetKeyDown("e")) {
            if (crouch == 1) crouch = 0;
            else crouch = 1;
        }

        playerBody.transform.position = transform.position;
        playerBody.transform.position+=new Vector3(0.0f,crouch*-crouchFactor, 0.0f);

        playerBody.transform.Rotate(-Input.GetAxis("Mouse Y"), Input.GetAxis("Mouse X") * 2, 0);
        float yComponent = Mathf.Deg2Rad * playerBody.transform.rotation.eulerAngles.y;
        Vector3 movement = new Vector3(moveVertical * Mathf.Sin(yComponent) + moveHorizontal * Mathf.Cos(yComponent), moveUp, moveVertical * Mathf.Cos(yComponent) + moveHorizontal * Mathf.Sin(yComponent));

        //movement.y= movement.magnitude* Mathf.Sin(Time.deltaTime);

        GetComponent<Rigidbody>().AddForce(movement * speed * Time.deltaTime);
    }

}