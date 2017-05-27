using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HealthPickup : Pickable {
    public int pickupValue;
    public AudioClip armorPickupSound;
    public bool isArmorPickup;
    private Player player;

	// Use this for initialization
	void Start () {
        player = GameObject.Find("FirstPersonCharacter").GetComponent<Player>(); ;

    }

    // Update is called once per frame
    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject != player.gameObject)
            return;

        AudioClip toPlay;
        if (isArmorPickup)
        {
            if (player.armor >= 100)
                return;

            player.armor += pickupValue;
            if (player.armor > 100)
                player.armor = 100;

            toPlay = armorPickupSound;
        }
        else {
            if (player.life >= 100)
                return;

            player.life += pickupValue;
            if (player.life > 100)
                player.life = 100;

            toPlay = pickUpSound;
        }

        if (!player.GetComponent<AudioSource>().isPlaying) {
            player.GetComponent<AudioSource>().PlayOneShot(toPlay, 1);
        }

        Destroy(gameObject);
    }
}
