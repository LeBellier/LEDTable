package fr.bellier.core.utils;

import fr.bellier.core.entities.Box;
import java.util.List;

/**
 *
 * @author LeBellier
 */
public class ArtnetService {

    private ArtnetService() {
    }

    public static ArtnetService getInstance() {
        return INSTANCE;
    }

    private static final ArtnetService INSTANCE = new ArtnetService();

    public int[] colorToByteArray(List<Box> boxes) {
        int[] dmx = new int[(3 * boxes.size())];
        for (Box box : boxes) {
            int i = box.getIndex();
            dmx[i * 3] = box.getRed();
            dmx[i * 3 + 1] = box.getGreen();
            dmx[i * 3 + 2] = box.getBlue();
        }
        return dmx;
    }

}
