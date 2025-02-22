/* 
 * ProviewR   Open Source Process Control.
 * Copyright (C) 2005-2025 SSAB EMEA AB.
 *
 * This file is part of ProviewR.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with ProviewR. If not, see <http://www.gnu.org/licenses/>
 *
 * Linking ProviewR statically or dynamically with other modules is
 * making a combined work based on ProviewR. Thus, the terms and
 * conditions of the GNU General Public License cover the whole 
 * combination.
 *
 * In addition, as a special exception, the copyright holders of
 * ProviewR give you permission to, from the build function in the
 * ProviewR Configurator, combine ProviewR with modules generated by the
 * ProviewR PLC Editor to a PLC program, regardless of the license
 * terms of these modules. You may copy and distribute the resulting
 * combined work under the terms of your choice, provided that every 
 * copy of the combined work is accompanied by a complete copy of 
 * the source code of ProviewR (the version used to produce the
 * combined work), being distributed under the terms of the GNU 
 * General Public License plus this exception.
 */

package jpwr.rt;
import java.util.Vector;
import java.util.ListIterator;
/**
 *  Storage class for alarms and events.
 *
 *  @author     Jonas Nylund
 */
public class MhData
{

  public int maxNrOfAlarms;
  public int maxNrOfEvents;
  public Vector<MhrEvent> alarmVec;
  public Vector<MhrEvent> eventVec;
  public int lastSyncIdx = 0;


  public MhData(int maxNrOfAlarms, int maxNrOfEvents)
  {
    this.maxNrOfAlarms = maxNrOfAlarms;
    this.maxNrOfEvents = maxNrOfEvents;
    this.alarmVec = new Vector<MhrEvent>(maxNrOfAlarms);
    this.eventVec = new Vector<MhrEvent>(maxNrOfEvents);
  }
  public int getNrOfAlarms()
  {
    return alarmVec.size();
  }
  public int getNrOfEvents()
  {
    return eventVec.size();
  }
  public MhrEvent getAlarm(int i)
  {
    return alarmVec.get(i);
  }
  public MhrEvent getEvent(int i)
  {
    return eventVec.get(i);
  }
  public void addMessToVectorInSortedOrder(Vector<MhrEvent> v, MhrEvent ev)
  {
    ListIterator<MhrEvent> iter = v.listIterator();
    MhrEvent vEv;
    while(iter.hasNext())
    {
      vEv = iter.next();
      if(ev.eventTime.compareTo(vEv.eventTime) >= 0)
      {
        iter.previous();
	iter.add(ev);
	return;
      }
    }
    try
    {
      iter.add(ev);
    }
    catch(UnsupportedOperationException e)
    {
      System.out.println(e.toString());
    }
    catch(Exception e)
    {
      System.out.println(e.toString());
    }
  }

  /**
   *  Description of the Method
   *
   *@param  ev  Description of the Parameter
   */
  public void insertNewMess(MhrEvent ev)
  {
    switch (ev.eventType)
    {
      case Mh.mh_eEvent_Alarm:
      case Mh.mh_eEvent_MaintenanceAlarm:
      case Mh.mh_eEvent_SystemAlarm:
      case Mh.mh_eEvent_UserAlarm1:
      case Mh.mh_eEvent_UserAlarm2:
      case Mh.mh_eEvent_UserAlarm3:
      case Mh.mh_eEvent_UserAlarm4:
        // Add to alarm list
	lastSyncIdx++;
	ev.syncIdx = lastSyncIdx;
        this.addMessToVectorInSortedOrder(alarmVec, ev);
        // Add copy to event list
        this.addMessToVectorInSortedOrder(eventVec, ev.getCopy());
        break;
      case Mh.mh_eEvent_Return:
        // Find the object in the alarm list
        for(int i = 0; i < alarmVec.size(); i++)
        {
          MhrEvent alEv = alarmVec.get(i);
          if((ev.targetId.nix == alEv.eventId.nix) && (ev.targetId.idx == alEv.eventId.idx))
          {
            // The alarm is acknowledged and can be removed
            if((alEv.eventStatus & Mh.mh_mEventStatus_NotAck) == 0)
            {
              alarmVec.removeElementAt(i);
            }
            // Set the return bit and display it
            else
            {
              alEv.eventStatus &= ~Mh.mh_mEventStatus_NotRet;
            }
            break;
          }
        }
        if((ev.eventFlags & Mh.mh_mEventFlags_Return) != 0)
        {
          // Add copy to event list
	  lastSyncIdx++;
	  ev.syncIdx = lastSyncIdx;
	  this.addMessToVectorInSortedOrder(eventVec, ev.getCopy());
        }
        break;
      case Mh.mh_eEvent_Block:
      case Mh.mh_eEvent_Reblock:
      case Mh.mh_eEvent_Cancel:
      case Mh.mh_eEvent_Unblock:
        // Add copy to event list
	lastSyncIdx++;
	ev.syncIdx = lastSyncIdx;
	this.addMessToVectorInSortedOrder(eventVec, ev.getCopy());
	break;
      case Mh.mh_eEvent_Ack:
        for(int i = 0; i < alarmVec.size(); i++)
        {
          MhrEvent alEv = alarmVec.get(i);
          if((ev.targetId.nix == alEv.eventId.nix) && (ev.targetId.idx == alEv.eventId.idx))
          {
            if((alEv.eventStatus & Mh.mh_mEventStatus_NotRet) == 0)
            {
              alarmVec.removeElementAt(i);
            }
            else
            {
              alEv.eventStatus &= ~Mh.mh_mEventStatus_NotAck;
            }
            break;
          }
        }
        if((ev.eventFlags & Mh.mh_mEventFlags_Ack) != 0)
        {
          // Add copy to event list
	  lastSyncIdx++;
	  ev.syncIdx = lastSyncIdx;
          this.addMessToVectorInSortedOrder(eventVec, ev.getCopy());
        }
        break;
      case Mh.mh_eEvent_Info:
      case Mh.mh_eEvent_InfoSuccess:
        // Add to alarm list
        if((ev.eventFlags & Mh.mh_mEventFlags_InfoWindow) != 0)
        {
	  lastSyncIdx++;
	  ev.syncIdx = lastSyncIdx;
	  this.addMessToVectorInSortedOrder(alarmVec, ev);
	}
        // Add copy to event list
        eventVec.add(0, ev.getCopy());
        break;
      case Mh.EventType_ClearAlarmList:
	 alarmVec.clear();
	 System.out.println("Clearing alarmlist");
      break;
      
      default:
        break;
    }
    if(alarmVec.size() > maxNrOfAlarms)
    {
      alarmVec.removeElementAt(alarmVec.size() - 1);
    }
    if(eventVec.size() > maxNrOfEvents)
    {
      eventVec.removeElementAt(eventVec.size() - 1);
    }
  }
}


